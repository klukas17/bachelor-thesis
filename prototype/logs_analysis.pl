#!/usr/bin/perl -w

@field=();

while (<>) {
    chomp;
    if (/\[.*?\] FRAME_COUNT = \d+, ITERATION = \d+, INDEX = \d+ --- (\d+)/) {
        push @field, $1;
    }
}
@field = reverse sort {$a <=> $b} @field;
print "@field\n";