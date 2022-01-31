cmake_minimum_required (VERSION 3.8)

include (cmake/app_datasources.cmake)

# copies file to <build>/data/example_data.tar.gz
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


declare_datasource (FILE 0overlap1bins1000length.txt
                    URL ${CMAKE_SOURCE_DIR}/test/data/0overlap1bins1000length.txt
                    URL_HASH SHA256=943663cf37f2bdb39ed23f23b3887a7b8ae9b8379e7c3cc6f4ba2014d0ad7878)
declare_datasource (FILE 0overlap8bins1000length.txt
                    URL ${CMAKE_SOURCE_DIR}/test/data/0overlap8bins1000length.txt
                    URL_HASH SHA256=15305e0d80769dbb37fea8b22ea88197284c8fa56b607f9cc17aef817f9e34e3)
declare_datasource (FILE 150overlap1bins1000length.txt
                    URL ${CMAKE_SOURCE_DIR}/test/data/150overlap1bins1000length.txt
                    URL_HASH SHA256=943663cf37f2bdb39ed23f23b3887a7b8ae9b8379e7c3cc6f4ba2014d0ad7878)
declare_datasource (FILE 150overlap8bins1000length.txt
                    URL ${CMAKE_SOURCE_DIR}/test/data/150overlap8bins1000length.txt
                    URL_HASH SHA256=a6bfc7eb27219d81c1c9d5f7c4491effd25c20b06091f38e2bcd464362c71cce)
declare_datasource (FILE bin_0_metadata.txt
                    URL ${CMAKE_SOURCE_DIR}/test/data/bin_0_metadata.txt
                    URL_HASH SHA256=a11fe5ad4fb063a6146fee1434314dc1227645784b47a5ba7b12bfb3492a0f89)

declare_datasource (FILE 8bins20window.ibf
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window.ibf
                    URL_HASH SHA256=47c9367e1be29ed40adc58a9cf72052375037562ae0e293bc07375b34042ca66)
declare_datasource (FILE 8bins23window.ibf
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window.ibf
                    URL_HASH SHA256=f0e3debd5f34f2392b0c7163cbc5be9642f4f95a4b4c017670992b8e78f56eb4)

declare_datasource (FILE 8bins20window0error50pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window0error50pattern1overlap.out
                    URL_HASH SHA256=fb9e916a394acb4d6bcd53556cffe7300bee4915ed61d67a8abdc5d1f412d8a8)
declare_datasource (FILE 8bins20window0error50pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window0error50pattern40overlap.out
                    URL_HASH SHA256=880e7c2c50943436f96dc026f03d5aed89672df8a3b0c02b6b72d20105024f77)
declare_datasource (FILE 8bins20window0error100pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window0error100pattern1overlap.out
                    URL_HASH SHA256=6631c798ab13356c18938aca418f16e474226ad50e4e08bbf364cfc422ae0fe7)
declare_datasource (FILE 8bins20window0error100pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window0error100pattern40overlap.out
                    URL_HASH SHA256=6631c798ab13356c18938aca418f16e474226ad50e4e08bbf364cfc422ae0fe7)
declare_datasource (FILE 8bins20window1error50pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window1error50pattern1overlap.out
                    URL_HASH SHA256=55550efe40e0b9ba12c55be2f6ea6756279e249f2eb94a3474736377461b6b6f)
declare_datasource (FILE 8bins20window1error50pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window1error50pattern40overlap.out
                    URL_HASH SHA256=55550efe40e0b9ba12c55be2f6ea6756279e249f2eb94a3474736377461b6b6f)
declare_datasource (FILE 8bins20window1error100pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window1error100pattern1overlap.out
                    URL_HASH SHA256=29ad8d60ab1b3f12efd7e47a79f85dba36808e213f90c74236810b6801b32886)
declare_datasource (FILE 8bins20window1error100pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins20window1error100pattern40overlap.out
                    URL_HASH SHA256=29ad8d60ab1b3f12efd7e47a79f85dba36808e213f90c74236810b6801b32886)
declare_datasource (FILE 8bins23window0error50pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window0error50pattern1overlap.out
                    URL_HASH SHA256=6631c798ab13356c18938aca418f16e474226ad50e4e08bbf364cfc422ae0fe7)
declare_datasource (FILE 8bins23window0error50pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window0error50pattern40overlap.out
                    URL_HASH SHA256=6631c798ab13356c18938aca418f16e474226ad50e4e08bbf364cfc422ae0fe7)
declare_datasource (FILE 8bins23window0error100pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window0error100pattern1overlap.out
                    URL_HASH SHA256=6631c798ab13356c18938aca418f16e474226ad50e4e08bbf364cfc422ae0fe7)
declare_datasource (FILE 8bins23window0error100pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window0error100pattern40overlap.out
                    URL_HASH SHA256=6631c798ab13356c18938aca418f16e474226ad50e4e08bbf364cfc422ae0fe7)
declare_datasource (FILE 8bins23window1error50pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window1error50pattern1overlap.out
                    URL_HASH SHA256=6ac8f4b0cecf89528ee509bb5d931d97c4630bd4a9ef1453b91068f9660848f1)
declare_datasource (FILE 8bins23window1error50pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window1error50pattern40overlap.out
                    URL_HASH SHA256=55550efe40e0b9ba12c55be2f6ea6756279e249f2eb94a3474736377461b6b6f)
declare_datasource (FILE 8bins23window1error100pattern1overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window1error100pattern1overlap.out
                    URL_HASH SHA256=9a0306117118149d3f8da6139e01a347847b9d5b0a009f53787648948185e5d1)
declare_datasource (FILE 8bins23window1error100pattern40overlap.out
                    URL ${CMAKE_SOURCE_DIR}/test/data/8bins23window1error100pattern40overlap.out
                    URL_HASH SHA256=9a0306117118149d3f8da6139e01a347847b9d5b0a009f53787648948185e5d1)
