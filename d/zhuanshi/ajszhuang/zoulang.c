// by yuchang
inherit ROOM;


string look_writing();


void create()
{
	set("short", "����");
	set("long", @LONG
����һ�����ȡ�����һ��֧������ĸ�ǽ�ϣ���һ�����붫
�����͵��ݶ�����������������������Ҳ�ò�������˸��ַ�
���ͼ�Σ�ÿ�������ĵ��ƺ�������˵һ���渶��˵Ĺ��¡�

LONG
	);

	set("exits", ([
                "east"  : __FILE__,
                "south" : __FILE__,
                "west"  : __FILE__,
                "north" : __FILE__,
        ]));


	setup();
}

void init()
{
     tell_object(this_player(), "����ú�������·���ֱ治�嶫��������"
                                "ֻ��һ������������!\n");
        
}


int valid_leave(object me, string dir)
{
	int kar;

	kar = 80 - me->query("kar");

	if (random(kar) == 0) 
	{
		tell_object(me, "���ߵþ�ƣ���������ڵ��˶��⡣\n");
		me->move(__DIR__"cjl");
		return 1;
	}

	return ::valid_leave(me,dir);
}



