#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});
mapping *data=({
    (["name":WHT"������"NOR,	"id":"bailong ma",]),
    (["name":HIR"������"NOR,	"id":"hongxu ma",]),
    (["name":HIG"��Ѫ��"NOR,	"id":"bixue ma",]),
    (["name":HIM"���ƾ�"NOR,	"id":"caiyun ju",]),
    (["name":HIY"÷��¹"NOR,	"id":"meihua lu",]),
    (["name":HIW"�׻���"NOR,	"id":"baihua ma",]),
    (["name":HIC"������"NOR,	"id":"qingtian ma",]),
    (["name":WHT"�׷��"NOR,	"id":"baifeng ju",]),
    (["name":HIR"��ͷ��"NOR,	"id":"hongtou ma",]),
    (["name":HIG"��ë��"NOR,	"id":"lvmao ju",]),
    (["name":HIM"�����"NOR,	"id":"zitian ju",]),
    (["name":HIY"������"NOR,	"id":"huanglong ju",]),
    (["name":HIW"������"NOR,	"id":"baiyun ma",]),
    (["name":HIC"�����"NOR,	"id":"qingfeng ma",]),
    (["name":WHT"��ɽ����"NOR,	"id":"bai ma",]),
    (["name":HIR"�ɹź���"NOR,	"id":"hong ma",]),
    (["name":HIG"����С��"NOR,	"id":"xiao ma",]),
    (["name":HIM"��ԭ����"NOR,	"id":"bao ju",]),
    (["name":HIY"��������"NOR,	"id":"han ma",]),
    (["name":HIW"������"NOR,	"id":"baiti ma",]),
    (["name":HIC"���౦��"NOR,	"id":"diqing baoju",]),
    (["name":WHT"�׹���"NOR,	"id":"baiguang ma",]),
    (["name":HIR"���뱦��"NOR,	"id":"hongxu baoju",]),
    (["name":HIG"��������"NOR,	"id":"fei ma",]),
    (["name":HIM"�Ͻ����"NOR,	"id":"zijin shenju",]),
    (["name":HIY"�ƽ�¹"NOR,	"id":"huangjin lu",]),
});

void create()
{
    mapping npc;
    npc = data[random(sizeof(data))];

    set_name(npc["name"],({ npc["id"] }));
    set("race", "Ұ��");
    set("gender", "����");
    set("age", 2 + random(3));
    set("long", "����һƥ��������ǧ�ҹ�а˰١�\n");
    set("ridable", 1);
    set("unit", "ƥ");
    set("value", 100000);
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
