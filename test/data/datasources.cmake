cmake_minimum_required (VERSION 3.16)

include (cmake/app_datasources.cmake)

declare_datasource (FILE database.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/database.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)
declare_datasource (FILE single_query.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single_query.fasta
                URL_HASH SHA256=387d0a3f091dd2b89af3498a2c92f4482279a42b718e9408af6307ad6ab0d293)
declare_datasource (FILE single_reference.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single_reference.fasta
                URL_HASH SHA256=53d633474b01a68927d3ab1fd970b200e96403bb1fdcc53feb0367a2093be273)
declare_datasource (FILE various_chromosome_lengths.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/various_chromosome_lengths.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)


declare_datasource (FILE 50overlap16bins13window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap16bins13window1errors.gff.out
                URL_HASH SHA256=48b48a6e020078b888fd59d80573e0963883e0621f49a4c49b4e81218089e8cd)
declare_datasource (FILE 50overlap16bins13window.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap16bins13window.bin
                URL_HASH SHA256=05b39e58030307d4fa3db594cd9761caac45cea52879596eef7835d9572d91cf)
declare_datasource (FILE 50overlap16bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap16bins13window.ibf
                URL_HASH SHA256=dab2338a53e3b1be5216223bb1c11850bd6a8dfc17386b011fdf2e82238d5567)
declare_datasource (FILE 50overlap16bins15window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap16bins15window1errors.gff.out
                URL_HASH SHA256=48b48a6e020078b888fd59d80573e0963883e0621f49a4c49b4e81218089e8cd)
declare_datasource (FILE 50overlap16bins15window.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap16bins15window.bin
                URL_HASH SHA256=05b39e58030307d4fa3db594cd9761caac45cea52879596eef7835d9572d91cf)
declare_datasource (FILE 50overlap16bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap16bins15window.ibf
                URL_HASH SHA256=84b4aecb516ae607c537be76e2020b8bc98a3858897627c5f9444c9e8fc5b613)
declare_datasource (FILE 50overlap4bins13window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap4bins13window1errors.gff.out
                URL_HASH SHA256=4d132142b70cc947710f9f05d9836c3d333d73bf760bee7b8d180c835862ec10)
declare_datasource (FILE 50overlap4bins13window.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap4bins13window.bin
                URL_HASH SHA256=fc540184c154647f4a2a8a7d5fb887969c63c269f2b2136872387e22a92e96c1)
declare_datasource (FILE 50overlap4bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap4bins13window.ibf
                URL_HASH SHA256=efc06869727d77d10c161f8e9e69c413fb25e135737fb3f7fb57cc6deb2b9e1f)
declare_datasource (FILE 50overlap4bins15window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap4bins15window1errors.gff.out
                URL_HASH SHA256=b6fc9b10d9a01edc78df81cc61e6ad7cdf356876c8a6e17184b78c392009d430)
declare_datasource (FILE 50overlap4bins15window.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap4bins15window.bin
                URL_HASH SHA256=fc540184c154647f4a2a8a7d5fb887969c63c269f2b2136872387e22a92e96c1)
declare_datasource (FILE 50overlap4bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap4bins15window.ibf
                URL_HASH SHA256=c2b4faa08853f8d7d66b4519c588a653199547ee5957c5a039be5c34d1b4d4fe)


declare_datasource (FILE 20overlap16bins.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap16bins.bin
                URL_HASH SHA256=07c233ad32a88fb4475fc797351721546e5ac7ac246579a64c333b5f0d84487b)
declare_datasource (FILE 20overlap16bins.index
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap16bins.index
                URL_HASH SHA256=82f7fbb1ea579c019446b6123d40b791ae25494a49569791e9be580b588f4ac3)
declare_datasource (FILE 20overlap4bins.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap4bins.bin
                URL_HASH SHA256=4a68c6f7c58394d507d86ba3dc8d35f6c4f3947607a118b653108185f18842de)
declare_datasource (FILE 20overlap4bins.index
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap4bins.index
                URL_HASH SHA256=3927d9ed102dd0f161b1cd77a5e47668b77138c4a59332aaf263c6e983996dfb)

declare_datasource (FILE write_out_20_16_reference_metadata.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_16/reference_metadata.bin
                URL_HASH SHA256=945fa1ba25e3616d06962dfbb12de7a77f8e9447401ec110dd384b303a36cfce)
declare_datasource (FILE write_out_20_16_reference_metadata.index
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_16/reference_metadata.index
                URL_HASH SHA256=d4dca0d7ff427b4fe5c07b0400809137164b6852cc274b77edb83cffe571b1b4)
declare_datasource (FILE write_out_20_4_reference_metadata.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_4/reference_metadata.bin
                URL_HASH SHA256=6bbafaa57788d018ab5fdf4bf0f19b59bcbd5f052355fe6ccb24ea0a12859199)
declare_datasource (FILE write_out_20_4_reference_metadata.index
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_4/reference_metadata.index
                URL_HASH SHA256=c23c6c536ad6d8597a2b48ceba235c3426c01afb3ddc80e4f20e62962da6ba83)
declare_datasource (FILE 8bins19window.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins19window.bin
                URL_HASH SHA256=3eb158a8595bc7718d11cbbcb79033e09083d06e6093c9afebdd122c15fc7f8f)
declare_datasource (FILE 8bins19window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins19window.ibf
                URL_HASH SHA256=a6417793f98a084f91727076998a042a898b89e84a1e217a5a5ae2037b0e6bcf)
declare_datasource (FILE 8bins23window.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins23window.bin
                URL_HASH SHA256=3eb158a8595bc7718d11cbbcb79033e09083d06e6093c9afebdd122c15fc7f8f)
declare_datasource (FILE 8bins23window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins23window.ibf
                URL_HASH SHA256=d138a58f36945527d1a92ed12d68136affa663670ee3d73b189a49fc9a4cbcd9)
declare_datasource (FILE bin_0.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_0.fasta
                URL_HASH SHA256=f9836f233fe459f8e387f8723dc030a10e44f3490cc1c89bed36222742bd6c35)
declare_datasource (FILE bin_1.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_1.fasta
                URL_HASH SHA256=782cb2eb50722e4a4fb2b5ca82b39817bf78305146a0ae086bab3273997e9237)
declare_datasource (FILE bin_2.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_2.fasta
                URL_HASH SHA256=5ff43c19f3b2d0d7cd113efd5941ff204a5e31820c6edc49c7c47f2d16388e77)
declare_datasource (FILE bin_3.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_3.fasta
                URL_HASH SHA256=0fc4021828129d1752dc2d9a1c163cfb642547ca8e889e969b119e6a2942a39f)
declare_datasource (FILE bin_4.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_4.fasta
                URL_HASH SHA256=d62dbba326f03da7fd4f0d61b460efcc73aee52582fc0903f5358978f33d1a9f)
declare_datasource (FILE bin_5.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_5.fasta
                URL_HASH SHA256=6f16ee171f262e6d1c621b94563adad42a5aab27afee48340d9c2273e67e396f)
declare_datasource (FILE bin_6.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_6.fasta
                URL_HASH SHA256=c4efc778c575e103041b300e0f110677d740c169e55421b9d16650fe92a8c872)
declare_datasource (FILE bin_7.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_7.fasta
                URL_HASH SHA256=45063104427a48892ba4ccb45cc295dc94760f08c1db90e6f3a73744591ada68)
declare_datasource (FILE bin_meta.index
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_meta.index
                URL_HASH SHA256=7b687e59bf717726dc0a2f0f97dc04cccf478e3266b4411d883359a46cb61f7b)
declare_datasource (FILE bin_paths.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_paths.txt
                URL_HASH SHA256=614e23263b689c7b4cc0ae41e99aeb5b43b351f865b4604f892320f2cc4377c7)
declare_datasource (FILE index.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/build/index.bin
                URL_HASH SHA256=f4a3dec17b486d55319a385da189709e6678c1cc03b4224d98dd9cb9c3b247f0)
declare_datasource (FILE index_copy_without_meta.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/index_copy_without_meta.ibf
                URL_HASH SHA256=a6417793f98a084f91727076998a042a898b89e84a1e217a5a5ae2037b0e6bcf)
declare_datasource (FILE index.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/index.ibf
                URL_HASH SHA256=cea3e922e2401224f9873bdea6eba2490e04d992b7a54062fdd138d250861293)


declare_datasource (FILE 8bins19window0error100pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern1query_every.gff.out
                URL_HASH SHA256=af90795ca7b27c762c2b9c8d2fa45b130fb528d038020279a1dea690f31bf8cd)
declare_datasource (FILE 8bins19window0error100pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern50query_every.gff.out
                URL_HASH SHA256=af90795ca7b27c762c2b9c8d2fa45b130fb528d038020279a1dea690f31bf8cd)
declare_datasource (FILE 8bins19window0error50pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern1query_every.gff.out
                URL_HASH SHA256=cc70823e384e508f353c15e651dea6982f93210849fe795d7f0f4e64978a7f71)
declare_datasource (FILE 8bins19window0error50pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern50query_every.gff.out
                URL_HASH SHA256=cc70823e384e508f353c15e651dea6982f93210849fe795d7f0f4e64978a7f71)
declare_datasource (FILE 8bins19window1error100pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern1query_every.gff.out
                URL_HASH SHA256=5e6059b76815b454926439a477cbb1e48a3e611a75c50bd5421aae258a9888b0)
declare_datasource (FILE 8bins19window1error100pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern50query_every.gff.out
                URL_HASH SHA256=5e6059b76815b454926439a477cbb1e48a3e611a75c50bd5421aae258a9888b0)
declare_datasource (FILE 8bins19window1error50pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern1query_every.gff.out
                URL_HASH SHA256=e87d9177c94fe52fb156dd09ff7d074dc88672d36e25ef625a08800fa94525a2)
declare_datasource (FILE 8bins19window1error50pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern50query_every.gff.out
                URL_HASH SHA256=3b8ab3cf3ddd8bde12610265053b6e388008548a684d3ce9ffe86cc0aded9dd0)
declare_datasource (FILE 8bins23window0error100pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern1query_every.gff.out
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window0error100pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern50query_every.gff.out
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window0error50pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern1query_every.gff.out
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window0error50pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern50query_every.gff.out
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window1error100pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern1query_every.gff.out
                URL_HASH SHA256=0bcbfdc35e39f3a7649aae50741220e438633c8b0d2f9aeb9e0c397f8d706f0f)
declare_datasource (FILE 8bins23window1error100pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern50query_every.gff.out
                URL_HASH SHA256=0bcbfdc35e39f3a7649aae50741220e438633c8b0d2f9aeb9e0c397f8d706f0f)
declare_datasource (FILE 8bins23window1error50pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern1query_every.gff.out
                URL_HASH SHA256=5824c908e91f53f9c9575191dba9a5491e5a0d5eb46fb3ffdcb13338c4016bc8)
declare_datasource (FILE 8bins23window1error50pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern50query_every.gff.out
                URL_HASH SHA256=1a8aa9aaff1ca312473b83c43c940978d0cd8f1765a61199c96d1f6d7e7b52ed)
declare_datasource (FILE query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/search/query.fq
                URL_HASH SHA256=65fbd58c14ca2b4c2274f44fff14dbfce54dc04a89cf6759e1a69cecba933130)


declare_datasource (FILE 16bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_all.gff
                URL_HASH SHA256=3ecd0e55e704cfd71442bd16805fe587de720e646cbe2d13675ed6249b30045f)
declare_datasource (FILE 16bins50overlap_reference_metadata.arg
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_reference_metadata.arg
                URL_HASH SHA256=eb44ecfa35432dfab9ad9fba9b6ca15a0d0702669558e36609b6b0e117cf3ac8)
declare_datasource (FILE 16bins50overlap_reference_metadata.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_reference_metadata.bin
                URL_HASH SHA256=416170a9f77e366f4d0c2c74f8e8417a0945b3b82cf609e9ceb7c30fc8577a2f)
declare_datasource (FILE 16bins50overlap_reference_metadata.index
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_reference_metadata.index
                URL_HASH SHA256=441ddb2fe1073b52f0b11f88be99d10a0f7e26e81b2133847b0e807f73a99161)
declare_datasource (FILE 8bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_dream_all.gff
                URL_HASH SHA256=f03c93ddb758a7e9ef89e3243dca9fb49b97a1ba3239408ffc30f8ff486982c8)
declare_datasource (FILE 8bins50overlap_reference_metadata.arg
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_reference_metadata.arg
                URL_HASH SHA256=bd1c333c11fefcb4fb82e0e58dcc0940f07061aabbb7ee22af555d23f34c1ae8)
declare_datasource (FILE 8bins50overlap_reference_metadata.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_reference_metadata.bin
                URL_HASH SHA256=6d6855c8bb964b619dcb0065e3a8c16ec5bde2c4ec99c345d37af8e2d9e79660)
declare_datasource (FILE 8bins50overlap_reference_metadata.index
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_reference_metadata.index
                URL_HASH SHA256=6604711fa9688e3279aa2dab5a83615cd319981e68a79dea75d48596427ccff8)
declare_datasource (FILE multi_seq_query.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/multi_seq_query.fasta
                URL_HASH SHA256=6d1260dc701802924487453c19715044cbeaa0f42021be8f2996bbaac1f24c58)
declare_datasource (FILE multi_seq_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/multi_seq_ref.fasta
                URL_HASH SHA256=a37f4be29ec99b66efb6ac235224b3145aadf8d5d6ff2c5c2f5324890170ce92)
declare_datasource (FILE stellar_truth.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth.gff
                URL_HASH SHA256=95bf8d1fcbcfde4dfea3cd2055bcf35be161e6b21519e2c936b3595ef37c017b)
declare_datasource (FILE stellar_truth_num12_dis13.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num12_dis13.gff
                URL_HASH SHA256=95bf8d1fcbcfde4dfea3cd2055bcf35be161e6b21519e2c936b3595ef37c017b)
declare_datasource (FILE stellar_truth_num12_dis3.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num12_dis3.gff
                URL_HASH SHA256=3ba650aa865f8190f21704275c9006e31a75c23b8adc27b1572d0f8a370285e6)
declare_datasource (FILE stellar_truth_num12_dis8.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num12_dis8.gff
                URL_HASH SHA256=18203e3ca735c4416fcc2444013640f13326babff0eea4456de604f0e1882e3e)
declare_datasource (FILE stellar_truth_num3_dis13.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num3_dis13.gff
                URL_HASH SHA256=315f57cedc484dcf074c4d8f0c199d73480fe0d9d5a58e5072df28c8e7d1694f)
declare_datasource (FILE stellar_truth_num3_dis3.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num3_dis3.gff
                URL_HASH SHA256=3ba650aa865f8190f21704275c9006e31a75c23b8adc27b1572d0f8a370285e6)
declare_datasource (FILE stellar_truth_num3_dis8.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num3_dis8.gff
                URL_HASH SHA256=f11cb143f32804c9fb51ee5c865fcb08fa1862b2fb67557ba95d17b38a4fb0e5)
declare_datasource (FILE stellar_truth_num9_dis13.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num9_dis13.gff
                URL_HASH SHA256=95bf8d1fcbcfde4dfea3cd2055bcf35be161e6b21519e2c936b3595ef37c017b)
declare_datasource (FILE stellar_truth_num9_dis3.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num9_dis3.gff
                URL_HASH SHA256=3ba650aa865f8190f21704275c9006e31a75c23b8adc27b1572d0f8a370285e6)
declare_datasource (FILE stellar_truth_num9_dis8.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num9_dis8.gff
                URL_HASH SHA256=18203e3ca735c4416fcc2444013640f13326babff0eea4456de604f0e1882e3e)


declare_datasource (FILE 1error.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/1error.gff
                URL_HASH SHA256=320bd247df63f0af37b069914a690e168460666f0c1b6040d3138bf387e2cd4a)
declare_datasource (FILE 1error.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/1error.gff.out
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 1error_stellar.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/1error_stellar.gff
                URL_HASH SHA256=01993f28b0973e612a7cc3e84abdbe551c9b47a6cc7507106ff4b48071c21613)
declare_datasource (FILE 2error_50pattern_index.arg
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/2error_50pattern_index.arg
                URL_HASH SHA256=2708b936a6fcf27a5faa672fac6d0dcb7837e832b8f3c0520fc928a0b65a7021)
declare_datasource (FILE 2error_50pattern_index.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/2error_50pattern_index.bin
                URL_HASH SHA256=b67193c38132e5f41550d8827acc10f8ae907938b8407f90377b1f68a925b547)
declare_datasource (FILE 2error.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/2error.gff
                URL_HASH SHA256=ae95fcdba6f8082424bb9a554439fd3d3335de6a24f89fb75ca039a9abfe8255)
declare_datasource (FILE 2error.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/2error.gff.out
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 2error_stellar.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/2error_stellar.gff
                URL_HASH SHA256=85cef348cd514cd12c442c71c7b44a6e44da4d3ea99e56752b3cc88d6f8d5b3f)
declare_datasource (FILE dummy_reads.fastq
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/dummy_reads.fastq
                URL_HASH SHA256=bf046a665167d983c19cf49c0366e09b0773860a679db97ed2a6a6e6a19e4cd9)
declare_datasource (FILE meta_param_deduction.arg
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/meta_param_deduction.arg
                URL_HASH SHA256=80fb0184ba1af94a20e263c8f20e0cf96358c2afc5c38f758a495cf505634440)
declare_datasource (FILE meta_param_deduction.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/meta_param_deduction.bin
                URL_HASH SHA256=19d9f4fd273cf03754e3f2dda4b3e767d6c96f8a227f5a5c5231262b18296f13)
declare_datasource (FILE query.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/query.fasta
                URL_HASH SHA256=40246c2de99c2d41508f3eec7fbfb1006001e6132c4b2fbdbe9ba500ce8be887)
declare_datasource (FILE reference_metadata.arg
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/reference_metadata.arg
                URL_HASH SHA256=a8541581af7ce61c953d43f5016bf27a35fd591be0c9e3f8a8f64917e3c1218f)
declare_datasource (FILE ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/ref.fasta
                URL_HASH SHA256=47f808d207c4c90afebbe1c8ab28990ec0e3e777c75ec787099279005428f3da)
declare_datasource (FILE seg_files.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/seg_files.txt
                URL_HASH SHA256=11bfde0a47b2f2f21e69e5ad5375ab3994d0475c4bda90cebdec5e87e95beed9)
declare_datasource (FILE s11111111.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111.bin
                URL_HASH SHA256=5cf4ecadc71f80ece94beef1081f8f16ec7963a5dfe95de30b1b8eb4d57b1dd8)
declare_datasource (FILE s1001.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001.bin
                URL_HASH SHA256=5cf4ecadc71f80ece94beef1081f8f16ec7963a5dfe95de30b1b8eb4d57b1dd8)
declare_datasource (FILE ref_bin_0.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_0.fasta
                URL_HASH SHA256=d27be5c9702697cf6e3573f469666f137a2c95b3c354deaab5151102a507a2fb)
declare_datasource (FILE s11111111_ref.0.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.0.header
                    URL_HASH SHA256=2bd3aa799c1689f366f58e468dc2b73537463e2244e00ef3eac1b055bef130c8)
declare_datasource (FILE s11111111_ref.0.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.0.minimiser
                    URL_HASH SHA256=b92f326fd1bc48b0858f65a043e48ee8cff275d1b605cc11f83951a9bbcf0d4f)
declare_datasource (FILE s1001_ref.0.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.0.header
                    URL_HASH SHA256=0754e4e66bf22b1ff841d04ed9ffd6521545a60fe1615e920c7a030a9f998a13)
declare_datasource (FILE s1001_ref.0.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.0.minimiser
                    URL_HASH SHA256=220ef0272c92c1529499408610eb2a7153fce7796fcbdd51201f86e64b39a192)
declare_datasource (FILE ref_bin_1.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_1.fasta
                URL_HASH SHA256=486d3e529acdd263896123389ece34774ed4448df33b5e6ae1ced672526a2efe)
declare_datasource (FILE s11111111_ref.1.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.1.header
                    URL_HASH SHA256=a04fafe6af22a41ad26eaaa43434df0fbdd975c67645d84a35de736186b5a680)
declare_datasource (FILE s11111111_ref.1.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.1.minimiser
                    URL_HASH SHA256=5abf0ea1fdd97d5bd0ac21445902f91d69e5652f5bf39cac9eb374fc5b54f483)
declare_datasource (FILE s1001_ref.1.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.1.header
                    URL_HASH SHA256=364d9f431c2ab580c77a02b91d4cd6aa8dd4c6c6dc2b3c74c3691faf32a78a37)
declare_datasource (FILE s1001_ref.1.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.1.minimiser
                    URL_HASH SHA256=220ef0272c92c1529499408610eb2a7153fce7796fcbdd51201f86e64b39a192)
declare_datasource (FILE ref_bin_2.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_2.fasta
                URL_HASH SHA256=76202a44ea78ea01420192e1266c5618b5e8131e65dee9c129c726240a687063)
declare_datasource (FILE s11111111_ref.2.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.2.header
                    URL_HASH SHA256=efacd3cfeaec4c6e17d2e54e846ca24d7db6e65b2709980a47616a60c89a5d90)
declare_datasource (FILE s11111111_ref.2.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.2.minimiser
                    URL_HASH SHA256=4cf2c1243a0a9b41818bea7d65873764063aeeed2c7428ea78a3ba8a345682fb)
declare_datasource (FILE s1001_ref.2.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.2.header
                    URL_HASH SHA256=364d9f431c2ab580c77a02b91d4cd6aa8dd4c6c6dc2b3c74c3691faf32a78a37)
declare_datasource (FILE s1001_ref.2.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.2.minimiser
                    URL_HASH SHA256=9dde0d2edefc7620ab4035c9223f7a519a8c2a03bbc1074290168b300172e8ab)
declare_datasource (FILE ref_bin_3.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_3.fasta
                URL_HASH SHA256=da5f19c86476464aeaa483baf47b387a30e4d35bffd0e4d5c8cc30b86171458b)
declare_datasource (FILE s11111111_ref.3.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.3.header
                    URL_HASH SHA256=b68d2e2d414ad85b241a95cc8a7803e7287ad91b141e21b6dea3d0c52e4383b5)
declare_datasource (FILE s11111111_ref.3.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.3.minimiser
                    URL_HASH SHA256=e2dae13eb7002cb5ce0bc1e26e76608a9b171649137ae85eaa8367fadef7ecf7)
declare_datasource (FILE s1001_ref.3.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.3.header
                    URL_HASH SHA256=e619d7b55293062695176f8099a17421c5dc26571e9744e59339786d5b6f6734)
declare_datasource (FILE s1001_ref.3.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.3.minimiser
                    URL_HASH SHA256=220ef0272c92c1529499408610eb2a7153fce7796fcbdd51201f86e64b39a192)
declare_datasource (FILE ref_bin_4.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_4.fasta
                URL_HASH SHA256=eaf85f135a9197732e6171b6652493f897e225b9970befea7945ff01e879688b)
declare_datasource (FILE s11111111_ref.4.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.4.header
                    URL_HASH SHA256=02ed6fd31d1adb0fe55d58f2f22facb9be51193cab24e634a9380400b7f04ebd)
declare_datasource (FILE s11111111_ref.4.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.4.minimiser
                    URL_HASH SHA256=644c16cfdd9647aecf657609de328d9dcb8b275d0de082f3acf06572ae92c8f6)
declare_datasource (FILE s1001_ref.4.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.4.header
                    URL_HASH SHA256=e619d7b55293062695176f8099a17421c5dc26571e9744e59339786d5b6f6734)
declare_datasource (FILE s1001_ref.4.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.4.minimiser
                    URL_HASH SHA256=f7f0a8292c4b2386eebfc24f160ec25d3e7eadfe5141f107deb8b8253f0e5f88)
declare_datasource (FILE ref_bin_5.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_5.fasta
                URL_HASH SHA256=0084dceed91ba50fd25675a82b92c51784284ebf84d4904f1eaa825c8e8add49)
declare_datasource (FILE s11111111_ref.5.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.5.header
                    URL_HASH SHA256=b12fb8c4ff2e6ec4deddf5883e7f89a3be27ef386e5b0d242f5522ce93d45c70)
declare_datasource (FILE s11111111_ref.5.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.5.minimiser
                    URL_HASH SHA256=e35c85d430b4e2f58e72888f0f427abd93b9504415a564a274095b69969f60f8)
declare_datasource (FILE s1001_ref.5.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.5.header
                    URL_HASH SHA256=2daccdb7ce627080ba994c238de4e618a4bbd6501b67cc456c1ddbe847d9b797)
declare_datasource (FILE s1001_ref.5.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.5.minimiser
                    URL_HASH SHA256=4a762e49f5450bb0124abea6f8aab66c914e669c37b6ace8f4ff4c6d3d4040b0)
declare_datasource (FILE ref_bin_6.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_6.fasta
                URL_HASH SHA256=0ab92343a1bd9610601183362f8719c397265a42cf47b7b8719bf8b66c1636e5)
declare_datasource (FILE s11111111_ref.6.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.6.header
                    URL_HASH SHA256=167b50db02aa4c53ed11c0505340ad09b83c7f9088dba990a23273643a2f483b)
declare_datasource (FILE s11111111_ref.6.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.6.minimiser
                    URL_HASH SHA256=f593ca9e1672ecc9d5b4fa9a9d9cc4f1c721f7dd9fa52ac82ba4288a24321473)
declare_datasource (FILE s1001_ref.6.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.6.header
                    URL_HASH SHA256=dcaad7664ae29715722dbfe99db9794abbe306883e7505b414a08bdc370855bf)
declare_datasource (FILE s1001_ref.6.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.6.minimiser
                    URL_HASH SHA256=aae89fc0f03e2959ae4d701a80cc3915918c950b159f6abb6c92c1433b1a8534)
declare_datasource (FILE ref_bin_7.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_7.fasta
                URL_HASH SHA256=7a94f3b63c2cdc1c4d2d58e51345a5447aa640c640b8bc44a501ec5c84c255e6)
declare_datasource (FILE s11111111_ref.7.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.7.header
                    URL_HASH SHA256=167b50db02aa4c53ed11c0505340ad09b83c7f9088dba990a23273643a2f483b)
declare_datasource (FILE s11111111_ref.7.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.7.minimiser
                    URL_HASH SHA256=f593ca9e1672ecc9d5b4fa9a9d9cc4f1c721f7dd9fa52ac82ba4288a24321473)
declare_datasource (FILE s1001_ref.7.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.7.header
                    URL_HASH SHA256=dcaad7664ae29715722dbfe99db9794abbe306883e7505b414a08bdc370855bf)
declare_datasource (FILE s1001_ref.7.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s1001/ref.7.minimiser
                    URL_HASH SHA256=aae89fc0f03e2959ae4d701a80cc3915918c950b159f6abb6c92c1433b1a8534)
