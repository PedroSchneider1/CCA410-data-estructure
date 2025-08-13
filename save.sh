#!/bin/bash
echo "####Update from github####"
git pull origin main
echo "####Add and commit####"
git add .
git commit -m "Salvo em `date +'%d-%m-%Y %H:%M:%S'`";
echo "####Update github####"
git push origin main