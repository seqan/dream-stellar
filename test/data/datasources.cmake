cmake_minimum_required (VERSION 3.8)

include (cmake/app_datasources.cmake)

declare_datasource (FILE 0overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/0overlap16bins.txt
                URL_HASH SHA256=39b3c960ce05e23d3208ab766388819a1e82b8036ae303e0eae37b425f66ef36)
declare_datasource (FILE 0overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/0overlap4bins.txt
                URL_HASH SHA256=88ee7061dc9dd86e7bd4cd8e37424bd73c3a74a7574d0b93d5519580d7cf1470)
declare_datasource (FILE 20overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/20overlap16bins.txt
                URL_HASH SHA256=b4d1c624381a18f120ecda7c4b7330fe34051503119ddefd8e08732fc20dca9f)
declare_datasource (FILE 20overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/20overlap4bins.txt
                URL_HASH SHA256=88ee7061dc9dd86e7bd4cd8e37424bd73c3a74a7574d0b93d5519580d7cf1470)
declare_datasource (FILE chromosome_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/chromosome_metadata.txt
                URL_HASH SHA256=435e36bbdb0d481070aca7a86d3b264359bc0c5029fbdaa48f17b9e0f8ad306b)
declare_datasource (FILE various_chromosome_lengths.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/various_chromosome_lengths.fasta
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


declare_datasource (FILE 8bins19window0error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern1overlap.out
                URL_HASH SHA256=5a9830d98f28f1bb24a7e50f3f03a37420d2cd134395eaa67842ad0f40652640)
declare_datasource (FILE 8bins19window0error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern40overlap.out
                URL_HASH SHA256=8ebbabb2a12b0da5547bc2011e8c957e958f265a1d35a3f5b38c0f1f5a495b84)
declare_datasource (FILE 8bins19window0error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern1overlap.out
                URL_HASH SHA256=c3ae42444715b8d86a1d9d093c91ab1a70180280a40d8ca7bba6c9ff9081c18b)
declare_datasource (FILE 8bins19window0error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern40overlap.out
                URL_HASH SHA256=6bb385f4fe7f5d3db1ad0a7c27297fcf59abebc70f72d2a667e91bd598bde7bc)
declare_datasource (FILE 8bins19window1error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern1overlap.out
                URL_HASH SHA256=a3473043ba3cf5e451455a00be56665031bce2abc5bb0aee8b88787c81925c40)
declare_datasource (FILE 8bins19window1error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern40overlap.out
                URL_HASH SHA256=a3473043ba3cf5e451455a00be56665031bce2abc5bb0aee8b88787c81925c40)
declare_datasource (FILE 8bins19window1error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern1overlap.out
                URL_HASH SHA256=bf5051a2e2408243e07efb15880e86c96d61d2778ae8ba33b0860f0e4edcea8e)
declare_datasource (FILE 8bins19window1error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern40overlap.out
                URL_HASH SHA256=48ca1b1f6191ceb46f15cd98c2526e5ecba551e88722b97a713aff0e774ec3ac)
declare_datasource (FILE 8bins23window0error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern1overlap.out
                URL_HASH SHA256=ad6f7c5dd1c4d49d8a48b1d8f77c603259eade6d202418c5030d00de3731e408)
declare_datasource (FILE 8bins23window0error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern40overlap.out
                URL_HASH SHA256=8ebbabb2a12b0da5547bc2011e8c957e958f265a1d35a3f5b38c0f1f5a495b84)
declare_datasource (FILE 8bins23window0error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern1overlap.out
                URL_HASH SHA256=c3ae42444715b8d86a1d9d093c91ab1a70180280a40d8ca7bba6c9ff9081c18b)
declare_datasource (FILE 8bins23window0error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern40overlap.out
                URL_HASH SHA256=bf5051a2e2408243e07efb15880e86c96d61d2778ae8ba33b0860f0e4edcea8e)
declare_datasource (FILE 8bins23window1error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern1overlap.out
                URL_HASH SHA256=379659b14a583cb0f2811a288b96f7d3c939ef920f9a50f843dcd780b7766e0f)
declare_datasource (FILE 8bins23window1error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern40overlap.out
                URL_HASH SHA256=17cc03873b85833003a6fca673b43d85801f4c25f5500cd69518d62ad5a3a587)
declare_datasource (FILE 8bins23window1error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern1overlap.out
                URL_HASH SHA256=bf5051a2e2408243e07efb15880e86c96d61d2778ae8ba33b0860f0e4edcea8e)
declare_datasource (FILE 8bins23window1error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern40overlap.out
                URL_HASH SHA256=e861caf3ae78bc7b72ecf364fccf9e40e3fff43bfe2ab12bfc0950f60dfed2b9)
declare_datasource (FILE query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/search/query.fq
                URL_HASH SHA256=f6c340b25877d6cf9836ac17c1d28437a9a8d54ebdd6d4c035d14827d883fc3b)
