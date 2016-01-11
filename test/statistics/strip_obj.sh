#!/bin/bash -xe
all='list-files,
f1,
f2,
f3,
f4'

get_combined() {
  rm $1
  for i in $all; do
    ls $i;
    objdump -d $i >> $1;
  done;
}

# This is for asm-files only.
seds() {
  combined=$1
  # Remove blank lines
  sed -i '/^$/d' $combined

  # Replace .type.*function with @function to act as marker.
  sed -i 's/^\t\.type.*function/function.marker/' $combined

  # Remove all the words starting with a '.'
  sed -i '/^\t\.\w/d' $combined
  sed -i '/^\.\w/d' $combined

  # Remove all the labels i.e. ending with a ':'
  sed -i '/\w:.*/d' $combined
  #  :%s/.*:\n//g

  # Remove $ops
  rm $ops

  # Get only the first word i.e. the instruction.
  awk '{print $1}' $combined &> $ops

  # Remove ; # and lines with a '.', lines which have filename. This should be done only after first ops have been collected.
  sed -i '/^;$/d' $ops
  sed -i '/^#$/d' $ops
  # TODO: Replace filenames. This does not work. sed -i '/\./d' $ops
}




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
