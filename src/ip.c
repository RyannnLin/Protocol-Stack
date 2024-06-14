#include "net.h"
#include "ip.h"
#include "ethernet.h"
#include "arp.h"
#include "icmp.h"

static int ID = 0;

/**
 * @brief 处理一个收到的数据包
 *
 * @param buf 要处理的数据包
 * @param src_mac 源mac地址
 */
void ip_in(buf_t *buf, uint8_t *src_mac)
{
    // TODO
    if (buf->len < sizeof(ip_hdr_t))
    {
        return;
    }
    ip_hdr_t *hdr = (ip_hdr_t *)buf->data;
    if ((hdr->version != IP_VERSION_4) || (swap16(hdr->total_len16) > buf->len))
    {
        return;
    }
    uint16_t checksum = hdr->hdr_checksum16;
    hdr->hdr_checksum16 = 0;
    if (checksum != checksum16((uint16_t *)buf->data, hdr->hdr_len * IP_HDR_LEN_PER_BYTE))
    {
        return;
    }
    hdr->hdr_checksum16 = checksum; //恢复头部校验和

    if (memcmp(net_if_ip, hdr->dst_ip, sizeof(net_if_ip)) != 0)
    {
        return;
    }

    if (buf->len > swap16(hdr->total_len16))
    {
        buf_remove_padding(buf, buf->len - swap16(hdr->total_len16));
    }

    if ((hdr->protocol != NET_PROTOCOL_ICMP) && (hdr->protocol != NET_PROTOCOL_UDP))
    {
        icmp_unreachable(buf, hdr->src_ip, ICMP_CODE_PROTOCOL_UNREACH);
    }
    buf_remove_header(buf, hdr->hdr_len * IP_HDR_LEN_PER_BYTE);

    net_in(buf, hdr->protocol, hdr->src_ip);
}

/**
 * @brief 处理一个要发送的ip分片
 *
 * @param buf 要发送的分片
 * @param ip 目标ip地址
 * @param protocol 上层协议
 * @param id 数据包id
 * @param offset 分片offset，必须被8整除
 * @param mf 分片mf标志，是否有下一个分片
 */
void ip_fragment_out(buf_t *buf, uint8_t *ip, net_protocol_t protocol, int id, uint16_t offset, int mf)
{
    // TODO
    buf_add_header(buf, sizeof(ip_hdr_t));

    ip_hdr_t *hdr = (ip_hdr_t *)buf->data;
    hdr->hdr_len = (uint8_t)(sizeof(ip_hdr_t) / IP_HDR_LEN_PER_BYTE);
    hdr->version = IP_VERSION_4;
    hdr->tos = 0;
    hdr->total_len16 = swap16(buf->len);
    hdr->id16 = swap16((uint16_t)id);
    hdr->flags_fragment16 = swap16(((uint16_t)mf << 13) + (offset & 0xfff)); // 保留位和DF置零
    hdr->ttl = IP_DEFALUT_TTL;
    hdr->protocol = protocol;
    hdr->hdr_checksum16 = 0;
    memcpy(hdr->dst_ip, ip, NET_IP_LEN);
    memcpy(hdr->src_ip, net_if_ip, NET_IP_LEN);
    hdr->hdr_checksum16 = checksum16((uint16_t *)buf->data, hdr->hdr_len * IP_HDR_LEN_PER_BYTE);

    arp_out(buf, ip);
    return;
}

/**
 * @brief 处理一个要发送的ip数据包
 *
 * @param buf 要处理的包
 * @param ip 目标ip地址
 * @param protocol 上层协议
 */
void ip_out(buf_t *buf, uint8_t *ip, net_protocol_t protocol)
{
    // TODO
    if (buf->len > ETHERNET_MAX_TRANSPORT_UNIT - sizeof(ip_hdr_t))
    {
        // 需要分片发送
        size_t bufLeft = buf->len; // 剩余的数据长度
        int offset = 0;
        size_t each_offset = (ETHERNET_MAX_TRANSPORT_UNIT - sizeof(ip_hdr_t)) / IP_HDR_OFFSET_PER_BYTE;
        size_t each_len = each_offset * IP_HDR_OFFSET_PER_BYTE;
        buf_t *ip_buf = &txbuf;
        while (bufLeft > each_len)
        {
            // 新建buf
            buf_init(ip_buf, each_len);
            memcpy(ip_buf->data, buf->data + offset * IP_HDR_OFFSET_PER_BYTE, each_len);
            // 发送
            ip_fragment_out(ip_buf, ip, protocol, ID, offset, 1);
            // 修改剩余buf长度、偏移量offset
            bufLeft -= each_len;
            offset += each_offset;
        }
        // 处理剩余长度
        buf_init(ip_buf, bufLeft);
        memcpy(ip_buf->data, buf->data + offset * IP_HDR_OFFSET_PER_BYTE, bufLeft);
        ip_fragment_out(ip_buf, ip, protocol, ID, offset, 0);
        ID++;
    }
    else
    {
        ip_fragment_out(buf, ip, protocol, ID++, 0, 0);
    }
    return;
}

/**
 * @brief 初始化ip协议
 *
 */
void ip_init()
{
    net_add_protocol(NET_PROTOCOL_IP, ip_in);
}