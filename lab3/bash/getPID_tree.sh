#!/bin/bash
pid=$1

get_ppid(){
	local pid=$1
	ppid=$( ps -p ${pid} -o ppid= )
	echo "${ppid}"
}

get_cmd(){
	local pid="$1"
	if [ $pid -eq 0 ] 
	then
		cmd="root"
	else
		cmd=$( ps -p ${pid} -o cmd= )
	fi
	echo ${cmd}
}

usage(){
	echo "Usage: $0 pid"
	exit 1
}

#Check for parameter
[[ $# -eq 0 ]] && usage

cmd=$( get_cmd ${pid} )
echo "Current process: ${pid} - ${cmd}"
echo "Get parent process:"
tab=""
while [ -n "${pid}" ] && [ ${pid} -ne 0 ]; do
	tab="++${tab}"
	ppid=$( get_ppid ${pid} )
	if [ -z "${ppid}" ]; then
		echo "process ${pid} is orphaned or doesn't exist"
		exit 1
	fi
	cmd=$( get_cmd ${ppid} )
	echo "${tab} ${ppid} - ${cmd}"
	pid=${ppid}
done

