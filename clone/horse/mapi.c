#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});
mapping *data=({
(["name":WHT"������"NOR,	"id":"bai longma",]),
(["name":HIR"������"NOR,	"id":"hong xuma",]),
(["name":HIG"��Ѫ��"NOR,	"id":"bi xuema",]),
(["name":HIM"���ƾ�"NOR,	"id":"cai yunju",]),
(["name":HIY"÷��¹"NOR,	"id":"mei hualu",]),
(["name":HIW"�׻���"NOR,	"id":"bai huama",]),
(["name":HIC"������"NOR,	"id":"qing tianma",]),
(["name":WHT"�׷��"NOR,	"id":"bai fengju",]),
(["name":HIR"��ͷ��"NOR,	"id":"hong touma",]),
(["name":HIG"��ë��"NOR,	"id":"lv maoju",]),
(["name":HIM"�����"NOR,	"id":"zi tianju",]),
(["name":HIY"������"NOR,	"id":"huang longju",]),
(["name":HIW"������"NOR,	"id":"bai yunma",]),
(["name":HIC"�����"NOR,	"id":"qing fengma",]),
(["name":WHT"��ɽ����"NOR,	"id":"bai ma",]),
(["name":HIR"�ɹź���"NOR,	"id":"hong ma",]),
(["name":HIG"����С��"NOR,	"id":"xiao ma",]),
(["name":HIM"��ԭ����"NOR,	"id":"bao ju",]),
(["name":HIY"��������"NOR,	"id":"han ma",]),
(["name":HIW"������"NOR,	"id":"bai tima",]),
(["name":HIC"���౦��"NOR,	"id":"diqing baoju",]),
(["name":WHT"�׹���"NOR,	"id":"bai guangma",]),
(["name":HIR"���뱦��"NOR,	"id":"hong baoju",]),
(["name":HIG"��������"NOR,	"id":"fei ma",]),
(["name":HIM"�Ͻ����"NOR,	"id":"zijin shenju",]),
(["name":HIY"�ƽ�¹"NOR,	"id":"huang jinlu",]),
});
void create()
{       
	mapping npc;
        npc=data[random(sizeof(data))];
        set_name(npc["name"],({ npc["id"] }));
        set("race", "Ұ��");
        set("gender", "����");
        set("age", 2+random(3));
        set("long", "����һƥ��������ǧ�ҹ�а˰١�\n");
        set("ridable", 1);
        set("value", 10000);
        set("int", 30);
        set("qi", 300);
        set("max_qi", 300);
        set("jing", 100);
        set("max_jing", 100);
        set("shen_type", 0);
        set("combat_exp", 50000);
        set("attitude", "peaceful");

        set("limbs", ({ "ͷ��", "����", "β��","����","ǰ��" }) );
        set("verbs", ({ "bite", "hoof" }) );
        set_temp("apply/attack", 50);
        set_temp("apply/armor", 15);
        set_temp("apply/damage", 25);

        setup();
}

