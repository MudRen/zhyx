#include <ansi.h>
inherit NPC;
void consider();
void create()
{
    set_name("������", ({"bu jingyun", "bu", "jingyun"}));
    set("nickname", HIY "��������" NOR );
    set("gender", "����");
    set("age", 25);
    set("long", 
        "���������»��������������ƣ��������˳ơ��������񡹡�\n");
    set("attitude", "peaceful");
    
    set("str", 100);
    set("int", 80);
    set("con", 86);
    set("dex", 240);
    set("chat_chance", 1);
    set("chat_msg", ({
        "������̾�˿����������� ���� �ҵ���������ȥ�� ������\n",
        "�����Ƶ�ͷ��˼����Ȼ���\n",
    }));
    set("inquiry", ([
        "����"     : "˭�ܰ����ҵ����ƣ���ʲô�¶���Ӧ��! \n",
        "�����ý�" : "�ٺ٣���������ֻ����֪��������ܡ�\n",
    ]));
    set("qi", 20000);
   set("max_qi", 20000);
    set("jing", 5000);
    set("max_jing", 5000);
    set("max_jingli", 3000);

    set("jingli", 3000);
    set("neili", 6000);
    set("max_neili", 20000);
    set("jiali", 300);
    
     set("combat_exp", 60000000);
     
  set_skill("force", 900);
    set_skill("bibo-shengong", 890);
     set_skill("tanzhi-shentong", 900);
   set_skill("unarmed", 1000);
    set_skill("luoying-shenzhang", 860);
     set_skill("dodge", 1100);
    set_skill("anying-fuxiang", 800);
    set_skill("parry", 900);
   set_skill("sword", 900);
    set_skill("qimen-wuxing",800);
    set_skill("literate",550);           // ����ʶ��
     set_skill("literate",1100);
    map_skill("force"  , "bibo-shengong");
    map_skill("unarmed", "tanzhi-shentong");
    map_skill("dodge"  , "anying-fuxiang");
    map_skill("parry"  , "luoying-shenzhang");
    
    create_family("���»�", 1, "����");


	setup();
    
    carry_object("/d/taohua/obj/bupao")->wear();

    
}

int accept_object(object who, object ob)
{
    
    if ( (string) ob->query("id") =="ling pai" ) {
        if (!(int)who->query_temp("tmark/ling")) who->set_temp("tmark/ling", 0);
        message_vision("�����ƿ��˿�$N���������ƣ����˵�ͷ��˵����\n"
                               "�ѵ��㽫�����ͻء������ҵĶ����Ҿ������ˡ�\n"
                               "��Ϊ����,�ҿ��Ը���������ܡ�\n", who);
        who->set("tmark/ling", 1);
        return 1;
    }
    return 0;
}
