// Room: /d/city/yws.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "ҽ����");
	set("long", @LONG
��������̨�Աߵ�ҽ���ң�ר�������������������˵Ľ���
��ʿ��ҽ���ҵ���߷���һ����ҩ�������и�ʽ������ҩƷ����
�ұ���һ����Ϣ�õĴ��������������˵���Ϣ֮�á�
LONG
);
	set("sleep_room", "1");
	set("exits", ([ /* sizeof() == 1 */
  "out" : __DIR__"leitai.c",
]));
	set("no_clean_up", 0);

	setup();
}
void init()
{
        add_action("do_get","get");
        add_action("do_drop","drop");
}
int do_get()
{
        write(this_player()->query("name")+"������ô���ֶ����ʲô����\n");
        return 1;
}
int do_drop()
{
        write(this_player()->query("name")+"�������Ҷ���������\n");
        return 1;
}

