// npc: for quest npc
// by sun..
#include <ansi.h>
inherit NPC;

string ask_job();
string ask_fail();

void create()
{
        set_name("Ҧ����", ({ "yao yueling","yueling","yao" }));
        set("title", HIM "������" NOR);
        set("gender", "Ů��");
        set("age", 20);
        set("per",25);
        
        set("no_kill", 1);
        set("no_fight",1);
        set("no_get", 1);

        set("inquiry", ([
                "job" : ( :ask_job: ),
                "����" : ( :ask_job: ),
                "fail" : ( :ask_fail: ),
                "ʧ��" : ( :ask_fail: ),
        ])),

        setup();
}

#include "/quest/include/yao.h" 

