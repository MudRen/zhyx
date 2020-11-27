inherit ROOM;

void create()
{
        set("short", "¹����");
        set("long", @LONG
���ŷ�������¹���塣¹�����ֳ�֥�̷壬�������һ��
���ӣ���Բ��ǣ��������ӵ���ð����ÿ���϶������������
ѩ����Ψ¹������Ȼֲ��ïʢ����ʢ��֥�ݣ�¹���֮����
�кס�ȸ������������ϣ���¹����ȣ����֥��֮�ơ�
LONG );
        set("exits", ([
                "south"   : __DIR__"baiyun",
                "east"    : __DIR__"longmen",
                "northdown" : __DIR__"famu",
        ]));
        set("objects", ([
                "/clone/quarry/lu" : 2,
                "/clone/quarry/diao" : 1,
        ]));
        set("outdoors", "guanwai");
        setup();
        //replace_program(ROOM);
}

void init()
{
                add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me = this_player();
        
        if (! arg || arg != "milin")
                return notify_fail("��Ҫ�������ﰡ��\n");
        
        me->move("/d/guanwai/milin.c");
        return 1;
}
