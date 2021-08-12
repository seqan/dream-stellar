# Sliding window 

[![Build Status](https://github.com/seqan/app-template/workflows/App%20CI/badge.svg)](https://github.com/seqan/app-template/actions?query=branch%3Amaster+workflow%3A%22App+CI%22)

## Quick run

`./sliding_window build ../../../A2-metagenome-snakemake/MG-2/metadata/bin_paths.txt --threads 8 --output index.out --size 80m`

`./sliding_window search --index index.out --query ../../../A2-metagenome-snakemake/data/MG-2/64/reads_e5_150/10.fastq --pattern 50 --output matches.out --overlap 10`

### A fast and space-efficient pre-filter for querying very large collections of nucleotide sequences

## Download and Installation

<details><summary>Prerequisites (click to expand)</summary>

* CMake >= 3.8
* GCC 9, 10 or 11 (most recent minor version)
* git

Refer to the [Seqan3 Setup Tutorial](https://docs.seqan.de/seqan/3-master-user/setup.html) for more in depth information.
</details>

<details><summary>Download current master branch (click to expand)</summary>

```bash
git clone --recurse-submodules https://github.com/eaasna/sliding-window
```

</details>

<details><summary>Building (click to expand)</summary>

```bash
cd sliding-window
mkdir -p build
cd build
cmake ..
make
```

The binary can be found in `bin`.

You may want to add the executable to your PATH:
```
export PATH=$(pwd)/bin:$PATH
raptor --version
```

</details>

## Example Data and Usage
A toy data set can be found [here](https://ftp.imp.fu-berlin.de/pub/seiler/raptor/).

```bash
wget https://ftp.imp.fu-berlin.de/pub/seiler/raptor/example_data.tar.gz
tar xfz example_data.tar.gz
```

After extraction, the `example_data` will look like:

```console
$ tree -L 2 example_data
example_data
├── 1024
│   ├── bins
│   └── reads
└── 64
    ├── bins
    └── reads
```

The `bins` folder contains a FASTA file for each bin and the `reads` directory contains a FASTQ file for each bin
containing reads from the respective bin (with 2 errors).
Additionally, `mini.fastq` (5 reads of all bins), `all.fastq` (concatenation of all FASTQ files) and `all10.fastq`
(`all.fastq` repeated 10 times) are provided in the `reads` folder.

In the following, we will use the `64` data set.
To build an index over all bins, we first prepare a file that contains one file path per line
(a line corresponds to a bin) and use this file as input:
```
seq -f "example_data/64/bins/bin_%02g.fasta" 0 1 63 > bin_paths.txt
sliding_window build bin_paths.txt --threads 8 --output index.out --size 80m
```

You may be prompted to enable or disable automatic update notifications. For questions, please consult
[the SeqAn documentation](https://github.com/seqan/seqan3/wiki/Update-Notifications).

Afterwards, we can search for all reads from bin 1:

```
sliding_window search --index index.out --query example_data/64/reads/mini.fastq --errors 2 --pattern 50 --output matches.out --overlap 10
```

Each line of the output consists of the read ID (in the toy example these are numbers) and the corresponding bins in
which they were found:
```text
0       0,
1       0,
2       0,
3       0,
4       0,
16384   1,
...
1015812 62,
1032192 63,
1032193 63,
1032194 63,
1032195 63,
1032196 63,
```

For a list of options, see the help pages:
```console
sliding_window --help
sliding_window build --help
sliding_window search --help
```

## Authorship and Copyright
The sliding window filter is based on Raptor. Raptor is being developed by [Enrico Seiler](mailto:enrico.seiler@fu-berlin.de), but also incorporates much work from
other members of [SeqAn](https://www.seqan.de).

### Citation
In your academic works (also comparisons and pipelines) please cite:
  * Seiler, E. et al. (2020). Raptor: A fast and space-efficient pre-filter for querying very large collections of nucleotide sequences. bioRxiv 2020.10.08.330985. doi: https://doi.org/10.1101/2020.10.08.330985

### Supplementary
The subdirectory `util` contains applications and scripts related to the paper.

### License
Raptor is open source software. However, certain conditions apply when you (re-)distribute and/or modify Raptor, please see the [license](https://github.com/seqan/raptor/blob/master/LICENSE.md).
