cmake_minimum_required (VERSION 3.8)

include (cmake/app_datasources.cmake)

# declare_datasource (FILE example_data.tar.gz
#                     URL https://ftp.imp.fu-berlin.de/pub/seiler/raptor/example_data.tar.gz
#                     URL_HASH SHA256=7c2e7bdbf573cfe2314c8255080a5d57d966722e8bfb53712e03d87ce463ff15)


# declare_datasource (FILE expected_results.tar.gz
#                     URL https://ftp.imp.fu-berlin.de/pub/seiler/raptor/expected_results.tar.gz
#                     URL_HASH SHA256=2685ef95ebea074514f4736888b493857f0327514684ef88d798b3f25df5fd5a)

declare_datasource (FILE bin_0.fasta
                    URL ${CMAKE_SOURCE_DIR}/test/data/bins/bin_0.fasta
                    URL_HASH SHA256=9a4a626225fdc66cfe2e05176adb9f140ea1d116d554463bc4163af5ad40a5b9)
declare_datasource (FILE bin_1.fasta
                    URL ${CMAKE_SOURCE_DIR}/test/data/bins/bin_1.fasta
                    URL_HASH SHA256=3003ce921b4b232061964da79c54616c94e9f785628e0bac741510427c9d3760)
declare_datasource (FILE bin_2.fasta
                    URL ${CMAKE_SOURCE_DIR}/test/data/bins/bin_2.fasta
                    URL_HASH SHA256=ef588e887403692bd770b2bc1f02eb66960552c963ea1ca1828356b8bbcbc38f)
declare_datasource (FILE bin_3.fasta
                    URL ${CMAKE_SOURCE_DIR}/test/data/bins/bin_3.fasta
		    URL_HASH SHA256=e1934131d117dc9a12ebef54c180eab7b580648265ad56928d8570a33bf1daa1)
declare_datasource (FILE bin_4.fasta
                    URL ${CMAKE_SOURCE_DIR}/test/data/bins/bin_4.fasta
                    URL_HASH SHA256=93f5a43a60c7beb175281f2f50674aa54e43320af8ac27976de8f96890c6d83b)
declare_datasource (FILE bin_5.fasta
                    URL ${CMAKE_SOURCE_DIR}/test/data/bins/bin_5.fasta
                    URL_HASH SHA256=84baf896ea1f289384dde1319c512749674bcd0e5f61d92522f768f15189d3f3)
declare_datasource (FILE bin_6.fasta
                    URL ${CMAKE_SOURCE_DIR}/test/data/bins/bin_6.fasta
                    URL_HASH SHA256=deb8c2cd17a59ec58d96c5ee9063b553917461661263f6ebeb44625a29076b87)
declare_datasource (FILE bin_7.fasta
                    URL ${CMAKE_SOURCE_DIR}/test/data/bins/bin_7.fasta
                    URL_HASH SHA256=13fbd6105b6544df86ae948b0dc85aed2d6e8fb711942fb5cc283602c9ccbc26)

declare_datasource (FILE query.fq
                    URL ${CMAKE_SOURCE_DIR}/test/data/query.fq
                    URL_HASH SHA256=9eea085c8c36c6d1ff2d33ec6affe7382c78cc33c415072ad414c90060ed05d9)

declare_datasource (FILE 8bins20window.ibf
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window.ibf
                    URL_HASH SHA256=47c9367e1be29ed40adc58a9cf72052375037562ae0e293bc07375b34042ca66)
declare_datasource (FILE 8bins23window.ibf
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window.ibf
                    URL_HASH SHA256=f0e3debd5f34f2392b0c7163cbc5be9642f4f95a4b4c017670992b8e78f56eb4)

declare_datasource (FILE 8bins20window0error50pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window0error50pattern1overlap.out
                    URL_HASH SHA256=2ca66e4efec7d05c303377456e3a3b4a73fcb0e27c6ad9aee5273c3c473f9613)
declare_datasource (FILE 8bins20window0error50pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window0error50pattern40overlap.out
                    URL_HASH SHA256=f6535102b8d72242b6011815c6d3c8d27fca53fd28bcc3f7a8b5f3514c9de91a)
declare_datasource (FILE 8bins20window0error100pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window0error100pattern1overlap.out
                    URL_HASH SHA256=89171ddb90c5656bcc0b1dda46f715140fd173ce8dddd4e0456f7a9102826e55)
declare_datasource (FILE 8bins20window0error100pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window0error100pattern40overlap.out
                    URL_HASH SHA256=003f180fda5415452e1f2f4e65e23e8c03b6f3e78060ba176c19a3d289729e30)
declare_datasource (FILE 8bins20window1error50pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window1error50pattern1overlap.out
                    URL_HASH SHA256=bd0299099e4ce70a5d92c6494fd5e7b07eaa034308ae657b57ccc7f5bf0afb83)
declare_datasource (FILE 8bins20window1error50pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window1error50pattern40overlap.out
                    URL_HASH SHA256=7b10baa0f9521330ea5452565c80d6ead6f2d7fdb221c1c24fff0fc14e483b1d)
declare_datasource (FILE 8bins20window1error100pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window1error100pattern1overlap.out
                    URL_HASH SHA256=3145b6497100f10327a7aabb56e9278b1cdb3fc31a127fc52189e7b0ed6f6fe1)
declare_datasource (FILE 8bins20window1error100pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window1error100pattern40overlap.out
                    URL_HASH SHA256=d317a2e15b1d4bc91a3207cbabcbf559a6271e939877db0a75c8c2bfd63e7972)
declare_datasource (FILE 8bins23window0error50pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window0error50pattern1overlap.out
                    URL_HASH SHA256=176ec7a3b561ebab3326c26053d2dba58ff366d42c30131f4fe014234a596c9e)
declare_datasource (FILE 8bins23window0error50pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window0error50pattern40overlap.out
                    URL_HASH SHA256=655a096621816fa8686de7e17f845ed972a54843eb7178cbe8b013aca2108320)
declare_datasource (FILE 8bins23window0error100pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window0error100pattern1overlap.out
                    URL_HASH SHA256=e33c074476d08c15aa3123facf14139a32661423558e70c3def3b5001379499f)
declare_datasource (FILE 8bins23window0error100pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window0error100pattern40overlap.out
                    URL_HASH SHA256=93abd26ec5594db69ac83c6868e5290bfe65ca98b43fd6c881af3c1e7e32e664)
declare_datasource (FILE 8bins23window1error50pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window1error50pattern1overlap.out
                    URL_HASH SHA256=f6cecb0933a238e915c481c4f1e7dbc3417618dc1894d9dd166c1107b4614581)
declare_datasource (FILE 8bins23window1error50pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window1error50pattern40overlap.out
                    URL_HASH SHA256=0481fc91ddd68f43aeaadc7c044954138adee97431dd642948cf5805738ac359)
declare_datasource (FILE 8bins23window1error100pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window1error100pattern1overlap.out
                    URL_HASH SHA256=841aec9ce34d6228c954067e6e279fe901ba5c93f5ad4d8e7fdd1d05a4e769d7)
declare_datasource (FILE 8bins23window1error100pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window1error100pattern40overlap.out
                    URL_HASH SHA256=609160a8b7d4488f5821139629756a4cd97db0af1650aab925405d000ec7c8a0)

