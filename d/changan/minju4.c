//Room: minju4.c

inherit ROOM;

void create ()
{
        set ("short", "���");
        set ("long", @LONG
������һ�����ס������̨�Ϸ��Ŵ��С��С����ɹޣ���������
����֮��Ķ��������ȴ��Ӵ󿪣�Ʈ��һ�ɻ��ݵ�����ζ�������ʮ��
���֣�һ�Ŵ�ľ���ӣ���Χ���ż������ӣ������������һ�𣬲�֪��
̸ʲô��
LONG);
        set("exits", 
        ([ //sizeof() == 1
        	"north" : __DIR__"huarui4",
        ]));

        setup();
        //replace_program(ROOM);
}