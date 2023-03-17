# valik [![build status][1]][2] [![codecov][3]][4]
<!--
    Above uses reference-style links with numbers.
    See also https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet#links.

    For example, `[![build status][1]][2]` evaluates to the following:
        `[link_text][2]`
        `[2]` is a reference to a link, i.e. `[link_text](https://...)`

        `[link_text]` = `[![build status][1]]`
        `[1]` is once again a reference to a link - this time an image, i.e. `[![build status](https://...)]
        `![build status]` is the text that should be displayed if the linked resource (`[1]`) is not available

    `[![build status][1]][2]` hence means:
    Show the picture linked under `[1]`. In case it cannot be displayed, show the text "build status" instead.
    The picture, or alternative text, should link to `[2]`.
-->

<!--
    This is the CI badge image:
        `https://img.shields.io/github/workflow/status/` - we do not use GitHub's badges as they are not customisable.
        `/seqan/app-template/` - owner/repository
        `CI%20on%20Linux` - name of the workflow as encoded URL (e.g., whitespace = %20)
        `master` - branch to show
        `?style=flat&logo=github` - use a GitHub-style badge
        `&label=App-Template%20CI` - text on the badge
        `"Open GitHub actions page"` - this text will be shown on hover
-->
[1]: https://img.shields.io/github/workflow/status/eaasna/valik/CI%20on%20Linux/master?style=flat&logo=github&label=valik%20CI "Open GitHub actions page"
<!--
    This is the CI badge link:
        `https://github.com/seqan/app-template/actions` - actions page of owner(seqan)/repository(app-template)
        `?query=branch%3Amaster` - only show actions that ran on the mater branch
-->
[2]: https://github.com/eaasna/valik/actions?query=branch%3Amaster
<!--
    This is the Codecov badge image:
        Codecov offers badges: https://app.codecov.io/gh/seqan/app-template/settings/badge
        While being logged in into Codecov, navigate to Settings->Badge and copy the markdown badge.
        Copy the image part of the markdown badge here.
    `"Open Codecov page"` - this text will be shown on hover
-->
[3]: https://codecov.io/gh/eaasna/valik/branch/master/graph/badge.svg?token=ZKGJTQ55MF
<!--
    This is the Codecov badge link:
        Codecov offers badges: https://app.codecov.io/gh/seqan/app-template/settings/badge
        While being logged in into Codecov, navigate to Settings->Badge and copy the markdown badge.
        Copy the URL part of the markdown badge here.
-->
[4]: https://codecov.io/gh/eaasna/valik

## Quick run: split and search single reference sequence
`valik split test/data/split/single_reference.fasta --reference-output reference_metadata.txt --segment-output segment_metadata.txt --bins 4`

`valik build --from-segments test/data/split/single_reference.fasta --seg-path segment_metadata.txt --ref-meta reference_metadata.txt --window 15 --kmer 13 --output seg_file_index.ibf --size 100k`

`valik search --index seg_file_index.ibf --threads 4 --query test/data/search/query.fq --pattern 50 --overlap 49 --error 1 --output search.gff --seg-path segment_metadata.txt`

```text
read-0  0,
read-1  0,
read-2  0,
read-3  0,
read-4  0,
read-5  1,
read-6  1,
read-7  1,
read-8  1,
read-9  1,
read-10 1,2,
```

Each line of the search output consists of a read ID and matching bin IDs.

For a detailed list of options, see the help pages:
```console
valik --help
valik split --help
valik build --help
valik search --help
```

### Distributed local search
The valik application employs an IBF based prefilter (Estonian: _valik_) for searching approximate local matches in a nucleotide sequence database. The IBF is created from the (w,k)-minimiser content of the reference database. The filter excludes parts of the reference database for each query read. Only reference sequences where an approximate local match for the query sequence was found are retained.
A local match is defined as:
* length >= `pattern`
* errors <= `errors`

where `pattern` is the pattern size and `errors` the allowed number of errors. Each read is divided into multiple possibly overlapping pattern. The (w, k)-minimiser content of each window is then queried in the IBF.

## Download and Installation

<details><summary>Prerequisites (click to expand)</summary>

* CMake >= 3.16.9
* GCC 10, 11 or 12 (most recent minor version)
* git

Refer to the [Seqan3 Setup Tutorial](https://docs.seqan.de/seqan/3-master-user/setup.html) for more in depth information.
</details>

<details><summary>Download current master branch (click to expand)</summary>

```bash
git clone --recurse-submodules https://github.com/eaasna/valik
```

</details>

<details><summary>Building (click to expand)</summary>

```bash
cd valik
mkdir -p build
cd build
cmake ..
make
```

The binary can be found in `bin`.

You may want to add the executable to your PATH:
```
export PATH=$(pwd)/bin:$PATH
valik --version
```

</details>

## Authorship and Copyright
The Valik application is an offshoot of Raptor [license](https://github.com/seqan/raptor/blob/master/LICENSE.md).
