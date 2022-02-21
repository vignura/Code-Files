#!/bin/bash
# echo "token path: ${1}"

# read the token from file
if [ -f ${1} ]; 
then
	token=$(cat ${1})
	echo "token: ${token}"
else
	echo "ERROR: invalid token path ${1}"
	exit
fi

# get the git remote
ret=$(git remote -v)
if [ $? != 0 ]; then
	echo "ERROR: ${PWD} does not contain a git repository!"
	exit
fi
# echo "${ret}"

#convert the returned string to an array
retArr=(${ret})
# echo "${retArr[1]}"

#check if origin is present
if [ ${retArr[0]} != "origin" ]
then
	echo "ERROR: no remote named origin present!"
	exit
fi

# get the existing origin url
originURL=${retArr[1]}
echo "origin URL: ${originURL}"

# check if token is already added
match="${token}@github.com"
if [[ "$originURL" == *"$match"* ]]; then
  echo "token already added"
  exit
fi

# add the token before "github.com"
# ref: https://unix.stackexchange.com/questions/369818/how-to-insert-a-string-into-a-text-variable-at-specified-position
match="github.com"
originURL="${originURL%%${match}*}${token}@${match}${originURL##*${match}}"
echo "updated URL: ${originURL}"

# change the url
git remote set-url origin ${originURL}
if [[ $? != 0 ]]; then
	echo "ERROR: changing origin URL failed"
fi