#include <ansi.h>
inherit RIVER;

void create()
{
	set("short", "���ͱ�");
	set("long", @LONG
�����������С�����ͱ��������ǻƺӣ�������ɳĮ��ֻ
��������Ƭ��������ޣ�ס���Ƕ��Ǵӹ���Ǩ�ƹ����ģ����
�Ծ�Ӫ�ֹ���ƷΪ�����������֯��ë��̺����������ÿ���
�ո����İ��ն�������ڶɹ��� (river)������ȥ�ϼ����Ӱ�
���������������Ƕ������Žд����ӡ�
LONG);
        set("arrive_room", "/d/huanghe/guchangcheng");
	set("exits", ([
		"northeast" : __DIR__"mingshazhou",
	]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

	set("outdoors", "lingzhou");
        set("coor/x",-3030);
	set("coor/y",2935);
	set("coor/z",0);
	setup();
        replace_program(RIVER);
}

