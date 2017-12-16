#!/usr/bin/perl

$a = $ARGV[0];
$b = $ARGV[1];
$n = $ARGV[2];

$totalsum = ($n * ($n + 1)) / 2;
$sum = $totalsum - ($a + $b);

$product = $a * $b;

print "sum = $sum, product = $product\n";
