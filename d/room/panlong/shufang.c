// shufang.c �������鷿

#include <ansi.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
	set("short", "�鷿");
	set("long", @LONG
�����������ӵ����˶���д�ֵĵط����ɾ��������ķ��ı���������
�İ����������档��ʱ����Ҳ������ǩ��һЩ������˵����
LONG );

	set("default_long", "������ROOM_NAME������ROOM_OWNER����д�ֵ�"/* EXAMPLE */
                            "�ط����ɾ��������ķ��ı���������İ�����" /* EXAMPLE */
                            "�����档��ʱROOM_OWNERҲ������ǩ��(sign"/* EXAMPLE */
                            ")һЩ������˵����");                  /* EXAMPLE */
                                                                       /* EXAMPLE */

	set("exits", ([
		"east" : __DIR__"jusuo",
	]));

        set("sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

