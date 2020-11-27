#include <ansi.h>
inherit NPC;


int do_leave();

void create()
{
        NPC_D->generate_cn_name(this_object());
        set("gender", "����");
        set("age", 60 + random(20));

        set("attitude", "friendly");
        set("str", 35);
        set("int", 15);
        set("con", 19);
        set("dex", 17);

        set("chat_chance", 100);
        set("chat_msg", ({
                (: do_leave :),
        }));

        setup();
        set_heart_beat(5);
        if (clonep()) keep_heart_beat();

        set("check_time", time());
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
           object ob = this_object();

      if ( environment(ob)->query("short") == ob->query("dest"))
      {
           remove_call_out("arrive");
           call_out("arrive", 2, ob);
       }
 }

int do_leave()
{
        object npc,me;       

        npc = this_object();
        me = query("leader");

        if ( time() - query("check_time") > 800 || ! me) 
         {
            message("vision", CYN + npc->name() + "����ææ���뿪�ˡ�\n"NOR,
                   environment(npc));
            destruct(npc);
            return 1;
         }
        
        if (! environment())
                return 0;
        if ( npc->query("arrived") == 1 )
                return 0;
        
        if ( random(10) == 1 && environment(me) == environment(npc) )
        {
            npc->start_busy(2);
            message_vision(HIG "$N��������ض�$n"
                           "˵������$n�����㰡���Ϻ��Ҹ������ˣ���\n"
                           "˵���һ�������ؿ���������һƨ��������·�ߡ�\n"NOR,
                           npc, me);
        }
       
        if ( time() - query("check_time") > 600  //����ʱ��
             || ! me || me->query("xquest/target_npc") != npc->name() )           
                                                         //û��ɾ�ȥȡ����      
        {

                  message("vision", HIY "�������ţ�" + npc->name() + "ͻȻ����"
                          "����������������Ѫ����\n�漴��ҵ�˵���������ˣ�"
                          "���ˣ������ҵĴ���������\nֻ������ǰδ����ȴ���һ"
                          "׮��Ը��ʵ�������Ŀѽ����\n"NOR,
                          environment(npc));

                  if ( me && environment(me) == environment(npc))
                  {
                          tell_object( me, RED"������һ���������������ˣ���"
                          + npc->name() + "Ҫ��һ�������ɾͶ��ˣ�"
                          "�������Ǻã���\n"NOR);
                  }


                  CHANNEL_D->do_channel(npc, "rumor",
                  "��˵"NOR HIY + npc->name() + NOR HIM"�������Ѹ߶�������御�"
                  "��ǰδ���糥��Ը��ʵ���ź���\n") ;
                  npc->die();
                  return 0;

        }
        return 1;
}


void arrive(object ob)
{
     object me, pay;
     int div, add;

     remove_call_out("arrive");
     me = ob->query("leader");
     
     if ( environment(ob)->query("short") == ob->query("dest")
          && ob->query("arrived") == 0 )
      {   
          if ( ! me->is_busy() ) me->start_busy(3);
          message("vision", HIC +ob->name() + "˵�����������벻����ʮ��δ����"
                  "�ʵ��������羰��Ȼ����羰���ɣ�Ψ��������ȫ��Ҳ��\n"
                  "�Ϻ��Ҹ���Ȫ֮ǰ�����������˵�һ�Σ���Ҳ���Ŀ�ˣ���л��λ"
                  + RANK_D->query_respect(me) + "���Ϻ��˴���Ը����\n"NOR,
                  environment(ob));
          ob->set("arrived",1);
          ob->set_leader(0);
          div = 1;     //����������������Ĳ���
          add = 80;
          message_vision(CYN "$N�ӻ����ͳ�һЩ��������$n��˵�������������"
                               "��һ·�ϵĳ���ѡ��������ˣ���\n" NOR,
                               ob, me);

          pay = new("/clone/money/silver");
          pay->set_amount(10+random(10));
          pay->move(me, 1);

          call_other(XQUEST, "reward", me, div, add);  //���н�������
          remove_call_out("finish");
          call_out("finish", 5, ob);
      }
}

void finish(object ob)
{
        message("vision", HIR +ob->name() + "˵�����������Ϻ������ڿ��԰��ĵ�"
                          "ȥ�ˡ���\n" NOR,
                          environment(ob));
        ob->die();
}


void unconcious()
{
        die();
}
