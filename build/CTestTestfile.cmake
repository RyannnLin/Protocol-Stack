# CMake generated Testfile for 
# Source directory: E:/college/code/C/CNLab/net-lab
# Build directory: E:/college/code/C/CNLab/net-lab/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(eth_in "E:/college/code/C/CNLab/net-lab/build/eth_in.exe" "E:/college/code/C/CNLab/net-lab/testing/data/eth_in")
set_tests_properties(eth_in PROPERTIES  _BACKTRACE_TRIPLES "E:/college/code/C/CNLab/net-lab/CMakeLists.txt;114;add_test;E:/college/code/C/CNLab/net-lab/CMakeLists.txt;0;")
add_test(eth_out "E:/college/code/C/CNLab/net-lab/build/eth_out.exe" "E:/college/code/C/CNLab/net-lab/testing/data/eth_out")
set_tests_properties(eth_out PROPERTIES  _BACKTRACE_TRIPLES "E:/college/code/C/CNLab/net-lab/CMakeLists.txt;119;add_test;E:/college/code/C/CNLab/net-lab/CMakeLists.txt;0;")
add_test(arp_test "E:/college/code/C/CNLab/net-lab/build/arp_test.exe" "E:/college/code/C/CNLab/net-lab/testing/data/arp_test")
set_tests_properties(arp_test PROPERTIES  _BACKTRACE_TRIPLES "E:/college/code/C/CNLab/net-lab/CMakeLists.txt;124;add_test;E:/college/code/C/CNLab/net-lab/CMakeLists.txt;0;")
add_test(ip_test "E:/college/code/C/CNLab/net-lab/build/ip_test.exe" "E:/college/code/C/CNLab/net-lab/testing/data/ip_test")
set_tests_properties(ip_test PROPERTIES  _BACKTRACE_TRIPLES "E:/college/code/C/CNLab/net-lab/CMakeLists.txt;129;add_test;E:/college/code/C/CNLab/net-lab/CMakeLists.txt;0;")
add_test(ip_frag_test "E:/college/code/C/CNLab/net-lab/build/ip_frag_test.exe" "E:/college/code/C/CNLab/net-lab/testing/data/ip_frag_test")
set_tests_properties(ip_frag_test PROPERTIES  _BACKTRACE_TRIPLES "E:/college/code/C/CNLab/net-lab/CMakeLists.txt;134;add_test;E:/college/code/C/CNLab/net-lab/CMakeLists.txt;0;")
add_test(icmp_test "E:/college/code/C/CNLab/net-lab/build/icmp_test.exe" "E:/college/code/C/CNLab/net-lab/testing/data/icmp_test")
set_tests_properties(icmp_test PROPERTIES  _BACKTRACE_TRIPLES "E:/college/code/C/CNLab/net-lab/CMakeLists.txt;139;add_test;E:/college/code/C/CNLab/net-lab/CMakeLists.txt;0;")
