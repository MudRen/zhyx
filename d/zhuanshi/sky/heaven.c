#include <ansi.h>
inherit ROOM;

#define FO  "/adm/npc/buddha"
void create()
{
        set("short", HIY "���������硿" NOR);
        set("long", HIW @LONG
�����������������磬�Ƿ�������ĵ��Ӿ۾�֮���ڡ�
���������ƺ���ϼ��������������磬˵������ׯ�Ϻ�ΰ��
��������Ĳ������������룬��Χ����̬���������޺���
��������ʮ��ΰ����������Լ�����������һ����ֺ�ߡ�
LONG NOR );
/*        set("exits", ([
                "down" : __DIR__"tianmen",
]));*/
        set("sleep_room", 1);
        set("no_fight", 1);       
        setup();  
        load_object(FO)->move(this_object());
      
}

