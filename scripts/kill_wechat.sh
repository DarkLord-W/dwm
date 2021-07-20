#! /bin/zsh

kill_wechat_with_pid()
{
	pids=`ps aux | grep WeChat.exe | grep -v grep |awk '{print $2}'`
	if [ -n "$pids" ]; then
		kill  $pids
	fi
}

kill_wechat_with_pid
