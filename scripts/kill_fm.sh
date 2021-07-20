#! /bin/zsh

kill_fm_with_pid()
{
	pids=`ps aux | grep thunar | grep -v grep |awk '{print $2}'`
	if [ -n "$pids" ]; then
		kill  $pids
	fi
}

kill_sftp_with_pid()
{
    pids=`ps aux | grep sftp | grep -v grep |awk '{print $2}'`
    if [ -n "$pids" ]; then
        kill  $pids
    fi
}

kill_fm_with_pid

kill_sftp_with_pid
