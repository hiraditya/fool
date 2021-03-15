#!/bin/bash -xe
# To merge repositories into the current.
# To see the log of the new repo use 'git log --follow -- unprefixed-filename'
# So if the file is repo/test.cpp use 'git log --follow -- test.cpp'
# I'm not sure how this will work when two files have the same name.
#
# Another trick to see all the commits in a subtree is:
# git log ${rn} will show you two SHA like these
# 388350c 2f866ad
# Then you can do git log 388350c..2f866ad, this will show all the commits from the subtree
#
# `git branch -a` will show newly created branches.
# You can delete them if you want.

merge_another() {
    repo="$1" # url of the repo
    rn="$2"   # name of the repo locally
    git remote add ${rn} ${repo}
    git fetch ${rn}
    git merge -s ours --no-commit --allow-unrelated-histories ${rn}/master
    git read-tree --prefix=${rn}/ -u ${rn}/master
    git commit -m "Imported ${rn} as a subtree."
    git pull -s subtree ${rn} master
}

merge_another $1 $2
push() {
    git push origin master
}
