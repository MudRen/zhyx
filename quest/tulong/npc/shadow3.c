#include <ansi.h>

inherit NPC;
int ask_bijian();

void create()
{
        set_name("������--��", ({ "ren woxing shadow", "shadow" }));
        set("title", BLU "������̽���"NOR );
        set("long", "ֻ����һ�ų��������ף���ɫѩ�ף����ް��Ѫɫ��üĿ���㣬
������ߣ�һͷ�ڷ���������һϮ��������ǰ������һ����Ҳ����õġ�\n");
        set("gender", "����");
        set("class", "scholar");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 130);
        set("per", 127);
        set("int", 130);
        set("con", 310);
        set("dex", 130);
        
        set("max_qi", 311000);
        set("max_jing", 100110);
        set("neili", 400110);
      set("max_neili", 4110000);
        set("jiali", 40110);
        set("combat_exp", 201100000);
        set("score", 50001100);

        set_skill("literate", 1100);
        set_skill("force", 2100);
        set_skill("dodge", 2100);
        set_skill("unarmed", 2010);
        set_skill("parry", 2100);
        set_skill("sword", 2100);
        set_skill("changquan", 2010);
        set_skill("kuihua-xinfa", 2100);
        set_skill("lingxu-bu", 2100);
        set_skill("damo-jian", 2100);
        set_skill("taiji-jian", 2100);
        set_skill("huifeng-jian", 2010);
        set_skill("taishan-sword", 2100);
        set_skill("hengshan-jian", 2010);
        set_skill("hengshan-sword", 2100);
        set_skill("huashan-sword", 2010);
        set_skill("songshan-sword", 2010);

        map_skill("dodge", "lingxu-bu");
        map_skill("force", "kuihua-xinfa");
        map_skill("unarmed", "changquan");
        map_skill("sword", "damo-jian");
        map_skill("parry", "damo-jian");

        set("inquiry", ([
                "����" :  (: ask_bijian :),
                "�Ƚ�" :  (: ask_bijian :),
        ]) );
        setup();
    carry_object("/d/wudang/obj/greyrobe")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

int ask_bijian()
{
        object obj, me = this_player(), ob = this_object();
        object room; 
       message_vision("$N����˵����������⿪��ӡ������ˡ���\n
$nЦ���������ÿ�������ӵ��������У�����Ȼ������ء���\n", me, ob );
        say(HIR"�����д��һ���������ֽ�������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("������̾�˿�����˵��������һ�С���\n");
                return 1;
        }
        command("enable sword taiji-jian");
        say(HIR"�����д��һ�������䵱��������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("������̾�˿�����˵�����������С���\n");
                return 1;
        }
        command("enable sword huifeng-jian");
        say(HIR"�����д��һ���������ҽ�������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("������̾�˿�����˵�����������С���\n");
                return 1;
        }
        command("enable sword songshan-sword");
        say(HIR"�����д��һ��������ɽ��������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("������̾�˿�����˵�����������С���\n");
                return 1;
        }
        command("enable sword taishan-sword");
        say(HIR"�����д��һ������̩ɽ��������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("������̾�˿�����˵�����������С���\n");
                return 1;
        }
        command("enable sword huashan-sword");
        say(HIR"�����д��һ��������ɽ��������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("������̾�˿�����˵�����������С���\n");
                return 1;
        }
        command("enable sword hengshan-sword");
        say(HIR"�����д��һ��������ɽ��������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("������̾�˿�����˵�����������С���\n");
                return 1;
        }
        command("enable sword hengshan-jian");
        say(HIR"�����д��һ��������ɽ��������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("������̾�˿�����˵����������û�����С���\n");
                return 1;
        }
        say("������˵��������λ" + RANK_D->query_respect(me)+"�����Ҿͷ����ǹ��ذɡ���\n"); 
          if(!( room = find_object("/d/tulong/spirit5")) )
                  room = load_object("/d/tulong/spirit5");
        if(objectp(room)) 
            { 
                 room->set("exits/northup", "/d/tulong/spirit6");
                message("vision","��������ǽ�ϰ���һ����һ�����ϵĽ��ݻ�������������\n\n\n\n",room);
        me->set_temp("m_success/��Ӱ",1);  
      message_vision (HIY"$N���Ͻ��ݣ���âէ��һ��С��������ڹ�â�΢Ц�������ֽ⿪�˵�������ӡ��лл�㡣\n\n"NOR,this_player());   
      message("channel:chat", HBMAG"��������硿"+me->query("name")+"�ֽ⿪�˵�������ӡ.\n"NOR,users());
      message_vision (HIY"��â�У�������--��Ҳ������ʧ�ˡ�\n"NOR,this_player());   
        destruct(this_object());
           }
        return 1;
}

