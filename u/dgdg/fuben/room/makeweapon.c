// makeweapon.c

inherit ROOM;

#define GANJIANG        "/adm/npc/ganjiang"
#define MOYE            "/adm/npc/moye"

void create()
{
	set("short","Զ��������");
	set("long",@LONG
������Ǵ�˵�е�Զ�������ң���Զ����һ��һŮ���Ǵ�˵�е�
�ɽ���Īа���ޣ��ԱߵĻ�¯��ȼ�������ܴ��
LONG
	);

	set("exits", ([
		"down" : "/d/city/kedian",
	]));

        GANJIANG->come_here();
        MOYE->come_here();


        set("no_fight", 1);
        set("no_sleep_room", 1);

	setup();
	//replace_program(ROOM);
}