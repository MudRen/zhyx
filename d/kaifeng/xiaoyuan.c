inherit ROOM;

void create()
{
        set("short", "СԺ");
        set("long", @LONG
��һ��̤���������ɵú������ã�ֻ������һƬ��������
���÷������������������������С·����������䣬����·
�ľ�ͷ���Ƿ��ɴ�ʦ����ס����Ҳ����ƽ���Ӵ���͵ĵط���
LONG);
        set("no_clean_up", 0);
        set("exits", ([
  		"north" : __DIR__"fangzhang",
  		"west" : __DIR__"cangjing",
	]));
        set("outdoors", "kaifeng");

        setup();
        //replace_program(ROOM);
}