// Room: /d/wizard/wizard_room.c

inherit ROOM;

void create()
{
	set("short", "��ʦ��Ϣ��");
	set("long", @LONG
���������ʦ�ļ���ۻ᳡�����շ�ˢ��������ǽ���Ϲ�
ͺͺ��ʲô��û�У����ӵ����������һ���ľ�����������
һ����ʦ���Բ�(board)�������������������һЩBUG������
������
LONG );

	set("exits", ([
               "down" : __DIR__"noname_room",
               "up" : "/u/xiner/d/test/test",
	]));
        set("valid_startroom", 1);
	set("no_fight", "1");
	setup();

	call_other("/clone/board/wiz_b", "???");
        //replace_program(ROOM);
}


