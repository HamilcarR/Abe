#!/bin/zsh

#this script tests the behaviour with threads

program=`$1`
argument=$2
for i in {1.."$argument"}
do
echo "$program"
done
