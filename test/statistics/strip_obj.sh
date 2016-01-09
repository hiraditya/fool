#!/bin/bash -xe

remove_function_tag() {
  # First 32 characters are spaces because the mnemonics start at 32 chars.
  sed -i 's/\d*\<.*>:/                                functionmarker/' $1
}

remove_first_n_characters_from_file() {
  sed -i 's/^.\{,32\}//' $1
}

restore() {
  cp $1.back $1
}

file=f
ops_only=$file.ops

restore $file
remove_function_tag $file
remove_first_n_characters_from_file $file
awk '{print $1}' $file > $ops_only
