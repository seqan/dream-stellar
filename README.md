# DREAM-Stellar [![build status][1]][2] [![codecov][3]][4]
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
        `/seqan/dream-stellar/` - owner/repository
        `CI%20on%20Linux` - name of the workflow as encoded URL (e.g., whitespace = %20)
        `main` - branch to show
        `?style=flat&logo=github` - use a GitHub-style badge
        `&label=dream-stellar%20CI` - text on the badge
        `"Open GitHub actions page"` - this text will be shown on hover
-->
[1]: https://img.shields.io/github/actions/workflow/status/seqan/dream-stellar/ci_linux.yml?branch=main&style=flat&logo=github&label=DREAM-Stellar%20CI "Open GitHub actions page"
<!--
    This is the CI badge link:
        `https://github.com/seqan/dream-stellar/actions` - actions page of owner/repository
        `?query=branch%3Amain` - only show actions that ran on the mater branch
-->
[2]: https://github.com/seqan/dream-stellar/actions?query=branch%3Amain
<!--
    This is the Codecov badge image:
        Codecov offers badges: https://app.codecov.io/gh/seqan/dream-stellar/settings/badge
        While being logged in into Codecov, navigate to Settings->Badge and copy the markdown badge.
        Copy the image part of the markdown badge here.
    `"Open Codecov page"` - this text will be shown on hover
-->
[3]: https://codecov.io/gh/seqan/dream-stellar/branch/main/graph/badge.svg "Open Codecov page"
<!--
    This is the Codecov badge link:
        Codecov offers badges: https://app.codecov.io/gh/seqan/dream-stellar/settings/badge
        While being logged in into Codecov, navigate to Settings->Badge and copy the markdown badge.
        Copy the URL part of the markdown badge here.
-->
[4]: https://codecov.io/gh/seqan/dream-stellar

## Getting started 
Find the set of local alignments between sets of reference and query sequences.

`dream-stellar build test/data/dream/ref.fasta --pattern 50 --output index.ibf`

`dream-stellar search --index index.ibf --query test/data/dream/query.fasta --error-rate 0.02 --output search.gff`

For a detailed list of options, see the help pages:
```console
dream-stellar --help
dream-stellar build --help
dream-stellar search --help
```

## Download and Installation

<details><summary>Prerequisites (click to expand)</summary>

* CMake >= 3.25
* GCC 10, 11 or 12 (most recent minor version)
* git

Refer to the [Seqan3 Setup Tutorial](https://docs.seqan.de/seqan/3-master-user/setup.html) for more in depth information.
</details>

<details><summary>Download current master branch (click to expand)</summary>

```bash
git clone https://github.com/seqan/dream-stellar
```

</details>

<details><summary>Building (click to expand)</summary>

```bash
cd dream-stellar
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

## DREAM-Stellar benchmark
The DREAM-Stellar [benchmark](https://github.com/eaasna/DREAM-stellar-benchmark/tree/v2.0) contains example workflows for using DREAM-Stellar for distributed local alignment.

## Authorship and Copyright
DREAM-Stellar is licensed under BSD 3, for details please see the [license]([https://github.com/seqan/dream-stellar/blob/main/LICENSE.md]).
