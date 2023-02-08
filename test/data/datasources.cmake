cmake_minimum_required (VERSION 3.16)

include (cmake/app_datasources.cmake)

declare_datasource (FILE single_query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single_query.fq
                URL_HASH SHA256=4c2987d0416a2bb76b14a37bd67d6c33a54a3c409ffe369007f0b66959f4dbd9)
declare_datasource (FILE single_reference.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single_reference.fasta
                URL_HASH SHA256=53d633474b01a68927d3ab1fd970b200e96403bb1fdcc53feb0367a2093be273)
declare_datasource (FILE various_chromosome_lengths.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/various_chromosome_lengths.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)
declare_datasource (FILE wget-log
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.1
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.1
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.10
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.10
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.11
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.11
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.12
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.12
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.13
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.13
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.2
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.2
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.3
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.3
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.4
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.4
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.5
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.5
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.6
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.6
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.7
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.7
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.8
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.8
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.9
                URL ${CMAKE_SOURCE_DIR}/test/data/split/wget-log.9
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)


declare_datasource (FILE 150overlap16bins13window1errors.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins13window1errors.out
                URL_HASH SHA256=876c81c445ba447055b4b91cb6ee641ffde85efba7dd2213e83fb410a00a5249)
declare_datasource (FILE 150overlap16bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins13window.ibf
                URL_HASH SHA256=bf2db42adc669ab73b074d74758ad56cf35d0c396031a0e73809b659fe8a76ce)
declare_datasource (FILE 150overlap16bins15window1errors.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window1errors.out
                URL_HASH SHA256=876c81c445ba447055b4b91cb6ee641ffde85efba7dd2213e83fb410a00a5249)
declare_datasource (FILE 150overlap16bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window.ibf
                URL_HASH SHA256=cb18705eaa1a94963969e7381efc3b5c099c241d7446a7292203c5d5b434b127)
declare_datasource (FILE 150overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins.txt
                URL_HASH SHA256=39501216962a5103aad09575248167cf5cfa63c96598ea8fcd7134421e1c8504)
declare_datasource (FILE 150overlap4bins13window1errors.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window1errors.out
                URL_HASH SHA256=654d90d615f45fa30e582bd70896331a7d1cc12b1b77c79beb02463e0e5bf285)
declare_datasource (FILE 150overlap4bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window.ibf
                URL_HASH SHA256=ce7b31acef135e024af9268b3416030d85e4c2828bc8c5dc3d1f18a34a03d373)
declare_datasource (FILE 150overlap4bins15window1errors.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins15window1errors.out
                URL_HASH SHA256=88df459a76a9ddb8c3f291d6b6ca6b3c739ce8d7533b0d3d281502c8b8c37482)
declare_datasource (FILE 150overlap4bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins15window.ibf
                URL_HASH SHA256=bc803cda05ef409a258420268d31e7ba3d8a5175b8292175cf40bdab10565ff5)
declare_datasource (FILE 150overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins.txt
                URL_HASH SHA256=cb60eb69a8519bbcb52da3e3f6524d11f560c11d7c70a094697a5f2254500b97)
declare_datasource (FILE reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/reference_metadata.txt
                URL_HASH SHA256=b82abe243ea2872d540d3548759997f93db2345351f76c93dd6ab40992abf1cd)


declare_datasource (FILE 0overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/0overlap16bins.txt
                URL_HASH SHA256=f41420e802d66d96bb3d2246d459791ebe5796da669600552a0c3eb43082345f)
declare_datasource (FILE 0overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/0overlap4bins.txt
                URL_HASH SHA256=171e201e20f2dc9d5d855b753fc7bf6abe7297ded613e727c0ed1dd69bbaf02f)
declare_datasource (FILE 20overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap16bins.txt
                URL_HASH SHA256=32a40e7211cd45832506f16d0b3a613a222efd0783463978a50aa85ecb302837)
declare_datasource (FILE 20overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap4bins.txt
                URL_HASH SHA256=171e201e20f2dc9d5d855b753fc7bf6abe7297ded613e727c0ed1dd69bbaf02f)
declare_datasource (FILE chromosome_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/chromosome_metadata.txt
                URL_HASH SHA256=368803a8d29419321ba9704bc7cbd52abf6f7b2f528d725ed54a5ecadf5c6ae3)


declare_datasource (FILE write_out_0_16_reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_16/reference_metadata.txt
                URL_HASH SHA256=368803a8d29419321ba9704bc7cbd52abf6f7b2f528d725ed54a5ecadf5c6ae3)
declare_datasource (FILE write_out_0_16_reference_segments.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_16/reference_segments.txt
                URL_HASH SHA256=f41420e802d66d96bb3d2246d459791ebe5796da669600552a0c3eb43082345f)
declare_datasource (FILE write_out_0_16_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_16/ref.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)
declare_datasource (FILE write_out_0_4_reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_4/reference_metadata.txt
                URL_HASH SHA256=368803a8d29419321ba9704bc7cbd52abf6f7b2f528d725ed54a5ecadf5c6ae3)
declare_datasource (FILE write_out_0_4_reference_segments.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_4/reference_segments.txt
                URL_HASH SHA256=171e201e20f2dc9d5d855b753fc7bf6abe7297ded613e727c0ed1dd69bbaf02f)
declare_datasource (FILE write_out_0_4_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_4/ref.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)
declare_datasource (FILE write_out_20_16_reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_16/reference_metadata.txt
                URL_HASH SHA256=368803a8d29419321ba9704bc7cbd52abf6f7b2f528d725ed54a5ecadf5c6ae3)
declare_datasource (FILE write_out_20_16_reference_segments.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_16/reference_segments.txt
                URL_HASH SHA256=32a40e7211cd45832506f16d0b3a613a222efd0783463978a50aa85ecb302837)
declare_datasource (FILE write_out_20_16_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_16/ref.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)
declare_datasource (FILE write_out_20_4_reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_4/reference_metadata.txt
                URL_HASH SHA256=368803a8d29419321ba9704bc7cbd52abf6f7b2f528d725ed54a5ecadf5c6ae3)
declare_datasource (FILE write_out_20_4_reference_segments.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_4/reference_segments.txt
                URL_HASH SHA256=171e201e20f2dc9d5d855b753fc7bf6abe7297ded613e727c0ed1dd69bbaf02f)
declare_datasource (FILE write_out_20_4_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_4/ref.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)
declare_datasource (FILE 8bins19window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins19window.ibf
                URL_HASH SHA256=3a13c890650bf857770816244ed9420295ad8bbe681dac335f687863fc79a603)
declare_datasource (FILE 8bins23window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins23window.ibf
                URL_HASH SHA256=250578b9e0c47df929ed628931441ada4569ab7df193a5ecb5c069e6339bd56a)
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
declare_datasource (FILE bin_paths.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_paths.txt
                URL_HASH SHA256=614e23263b689c7b4cc0ae41e99aeb5b43b351f865b4604f892320f2cc4377c7)
declare_datasource (FILE wget-log
                URL ${CMAKE_SOURCE_DIR}/test/data/build/wget-log
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.1
                URL ${CMAKE_SOURCE_DIR}/test/data/build/wget-log.1
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.2
                URL ${CMAKE_SOURCE_DIR}/test/data/build/wget-log.2
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.3
                URL ${CMAKE_SOURCE_DIR}/test/data/build/wget-log.3
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)


declare_datasource (FILE 8bins19window0error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern1overlap.out
                URL_HASH SHA256=b548f54e61de7d46e00fb31f657e6e861efda14cd1dc7120c5e374d7355add69)
declare_datasource (FILE 8bins19window0error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern40overlap.out
                URL_HASH SHA256=bd933bc63c61c16c62f0279a70f7a68da10213cf144ffd4ffafa683175e51aa1)
declare_datasource (FILE 8bins19window0error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern1overlap.out
                URL_HASH SHA256=bf5051a2e2408243e07efb15880e86c96d61d2778ae8ba33b0860f0e4edcea8e)
declare_datasource (FILE 8bins19window0error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern40overlap.out
                URL_HASH SHA256=bf5051a2e2408243e07efb15880e86c96d61d2778ae8ba33b0860f0e4edcea8e)
declare_datasource (FILE 8bins19window1error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern1overlap.out
                URL_HASH SHA256=0c5c175e3c5f5025e82b7bf1c8b45dbb08a9a74c035cfb940c111f1cd04771e1)
declare_datasource (FILE 8bins19window1error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern40overlap.out
                URL_HASH SHA256=0c5c175e3c5f5025e82b7bf1c8b45dbb08a9a74c035cfb940c111f1cd04771e1)
declare_datasource (FILE 8bins19window1error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern1overlap.out
                URL_HASH SHA256=56195c5996df15fd068652f000db1d1f8414d9f8ccb9d085ec764c0ecff1d3e6)
declare_datasource (FILE 8bins19window1error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern40overlap.out
                URL_HASH SHA256=65bc85799d8de009d65e0f570240919c2be6bdbd41332c5705e7b1b81e8dfd56)
declare_datasource (FILE 8bins23window0error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern1overlap.out
                URL_HASH SHA256=b548f54e61de7d46e00fb31f657e6e861efda14cd1dc7120c5e374d7355add69)
declare_datasource (FILE 8bins23window0error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern40overlap.out
                URL_HASH SHA256=bd933bc63c61c16c62f0279a70f7a68da10213cf144ffd4ffafa683175e51aa1)
declare_datasource (FILE 8bins23window0error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern1overlap.out
                URL_HASH SHA256=bf5051a2e2408243e07efb15880e86c96d61d2778ae8ba33b0860f0e4edcea8e)
declare_datasource (FILE 8bins23window0error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern40overlap.out
                URL_HASH SHA256=bf5051a2e2408243e07efb15880e86c96d61d2778ae8ba33b0860f0e4edcea8e)
declare_datasource (FILE 8bins23window1error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern1overlap.out
                URL_HASH SHA256=c884508bcaff39124968b565961716107077b96fd53b5807a00f2e0a6e5b2b6c)
declare_datasource (FILE 8bins23window1error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern40overlap.out
                URL_HASH SHA256=c884508bcaff39124968b565961716107077b96fd53b5807a00f2e0a6e5b2b6c)
declare_datasource (FILE 8bins23window1error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern1overlap.out
                URL_HASH SHA256=bf5051a2e2408243e07efb15880e86c96d61d2778ae8ba33b0860f0e4edcea8e)
declare_datasource (FILE 8bins23window1error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern40overlap.out
                URL_HASH SHA256=faec5a0cb474076799d0bd8d754c55d043f99400c8abc294820d47282f86bc65)
declare_datasource (FILE query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/search/query.fq
                URL_HASH SHA256=70bce56dd6d9b28d14f414e4edaa70fbf848e997263e66742a9f2375a0508133)
declare_datasource (FILE wget-log
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.1
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.1
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.10
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.10
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.11
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.11
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.12
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.12
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.13
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.13
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.14
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.14
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.15
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.15
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.16
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.16
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.17
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.17
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.18
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.18
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.19
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.19
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.2
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.2
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.20
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.20
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.21
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.21
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.22
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.22
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.23
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.23
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.24
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.24
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.25
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.25
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.26
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.26
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.27
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.27
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.28
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.28
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.29
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.29
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.3
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.3
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.30
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.30
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.4
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.4
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.5
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.5
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.6
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.6
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.7
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.7
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.8
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.8
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE wget-log.9
                URL ${CMAKE_SOURCE_DIR}/test/data/search/wget-log.9
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)


declare_datasource (FILE 10overlap_full.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/10overlap_full.gff
                URL_HASH SHA256=48e79e6cd9c0672a0396eda3c3e27efdac980d6b1d77a7273e8a34859abb4c2a)
declare_datasource (FILE 16bins10overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins10overlap_dream_all.gff
                URL_HASH SHA256=955057f355600ec93a965fc9cfca6092f06e6ee3b3fd1f9e6590334381bbd1c5)
declare_datasource (FILE 16bins10overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins10overlap_dream_consolidated.gff
                URL_HASH SHA256=296b99ee23f03f859274b88f5f6ffe08ac15a41f419282bf2a608dfdbd0f6ac7)
declare_datasource (FILE 16bins10overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins10overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE 16bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_all.gff
                URL_HASH SHA256=e30f06f9076e45c3cad53fd7ca217f293a546f325fa3d0f448d654607048e44c)
declare_datasource (FILE 16bins50overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_consolidated.gff
                URL_HASH SHA256=e436b20ab0b35bc0c9bf973c4a609162c8b4247c5a93c9fb52a786ea8cccb4d4)
declare_datasource (FILE 16bins50overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE 50overlap_full.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/50overlap_full.gff
                URL_HASH SHA256=6a073b53e85d4e099dd3f875e1257fbccce866e5738763729818e6297c7cb4be)
declare_datasource (FILE 8bins10overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins10overlap_dream_all.gff
                URL_HASH SHA256=3644af79d5732c2d0d515db6733e5c13d67d4b0840176ee0e0d4058b1d3eafff)
declare_datasource (FILE 8bins10overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins10overlap_dream_consolidated.gff
                URL_HASH SHA256=296b99ee23f03f859274b88f5f6ffe08ac15a41f419282bf2a608dfdbd0f6ac7)
declare_datasource (FILE 8bins10overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins10overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE 8bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_dream_all.gff
                URL_HASH SHA256=b03c92c88ad507b5a48111538552dd29cd491dc1eb365e3db739c5a99b4e8409)
declare_datasource (FILE 8bins50overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_dream_consolidated.gff
                URL_HASH SHA256=e436b20ab0b35bc0c9bf973c4a609162c8b4247c5a93c9fb52a786ea8cccb4d4)
declare_datasource (FILE 8bins50overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE multi_seq_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/multi_seq_ref.fasta
                URL_HASH SHA256=24d5bf54edf054b7407a0bc4707b72383b9467c051839a6cbd8ec8e2b6bb65f9)
declare_datasource (FILE query_e0.05.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/query_e0.05.fasta
                URL_HASH SHA256=b107238db9e0c0515b33fff570a787a86126789a0341bd2fdb52c6c607772f8d)
