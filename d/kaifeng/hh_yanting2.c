inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���ӵ��м����һ�Ŵ����ӣ��������������ʮ���ˡ���
�ӵ�һ��ͨ����������һ�߿���ȥ�������컨�����ķ�Ӣ��
���п��˶�ʱ���������ﶼ�����£��ɴ���ǰԺ¶�����硣
LONG);
        set("no_clean_up", 0);
        set("exits", ([
  		"west" : __DIR__"hh_zoulang5",
	]));
        setup();
        //replace_program(ROOM);
}