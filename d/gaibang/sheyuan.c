//room: sheyuan.c
inherit ROOM;

void create()
{
	set("short","��԰");
	set("long", @LONG
������ؤ����ӵ���԰��ؤ�����������ӣ�������ԣ����ⳣ
���߳��ַ����վ��쳤������������ѱ��֮�������������ߣ�ǽ��
Ҳ�����ߣ�������Ҳ���´����ߣ���֦��Ҳ�������ߣ������㲻�ľ���
LONG );
	set("exits",([
		"west"  : "/d/city/pomiao",
	]));
	set("outdoors", "city");
	set("objects",([
		"/clone/beast/jinshe" :1,
		"/clone/beast/dushe" :1,
		"/clone/beast/fushe" :1,
		"/clone/beast/qingshe" :1,
		"/clone/beast/wubushe" :1,
	]));
	setup();
	replace_program(ROOM);
}

