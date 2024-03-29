#!/usr/bin/env bash

set -e

# This script assumes it's located in the root directory of the git repository.
SCRIPTDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOTDIR="${SCRIPTDIR}" # This now directly references the script's directory.

set -x

# see also ".mailmap" for how email addresses and names are deduplicated
cat > "${ROOTDIR}/AUTHORS" <<- EOF
        # File @generated by hack/generate-authors.sh. DO NOT EDIT.
        # This file lists all contributors to the repository.
        # See hack/generate-authors.sh to make modifications.

        $(git -C "$ROOTDIR" log --format='%aN <%aE>' | LC_ALL=C.UTF-8 sort -uf)
EOF

