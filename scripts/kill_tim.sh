#! /bin/zsh

kill_tim_with_pid()
{
	pids=`ps aux | grep TIM | grep -v grep |awk '{print $2}'`
	if [ -n "$pids" ]; then
		kill  $pids
	fi
}

kill_tim_with_pid
