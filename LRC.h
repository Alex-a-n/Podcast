typedef struct lrc {
	int m_time;
	char lrc_buf[200];
	struct lrc* front;
	struct lrc* next;
}LRC;
#pragma once
