
//�������  Ȥζ����ȡ����������

#include <ansi.h>
              
inherit NPC;
inherit F_UNIQUE;

#define BAG           "/u/sanben/xquest/obj/bag"
#define MIRROR        "/u/sanben/task/mirror"
#define HULU_INSIDE   "/u/sanben/obj/hulu_inside"


int ask_quest();
int ask_cancel();
int ask_mirror();
int ask_hulu();

void create()
{         seteuid(getuid());
        set_name("�������", ({ "zixu daoren", "zixu", "daoren" }));
        set("long", @LONG
�������ŵ��ۣ��뷢�԰ף�һ���ɷ���ǵ���
�ɡ�����������кųơ��������С���������
��������ˡ���˵�������ѵõ����ɣ���ͨ��
�硣
LONG);
        set("nickname", HIW "�ɷ����" NOR);
        set("title", HIC "����۹���" NOR);
        set("gender", "����" );
        set("age", 108);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);

        set("inquiry", ([
                       "����"      : (: ask_quest :),
                       "����"      : (: ask_quest :),
                       "ȡ��"      : (: ask_cancel :),
                       "cancel"    : (: ask_cancel :),
                       "Ǭ������"      : (: ask_mirror :),
                       "����"      : (: ask_mirror :),
                       "mirror"      : (: ask_mirror :),    
//              "�Ͻ��«"    : (: ask_hulu :),
//                 "hulu"    : (: ask_hulu :),
        ]));

        set_skill("force", 500);
        set_skill("huntian-baojian", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("lunhui-jian", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("buddhism", 500);
        set_skill("taoism", 500);
        set_skill("literate", 500);
        set_skill("martial-cognize", 500);

        map_skill("force", "huntian-baojian");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("unarmed", "huntian-baojian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("sword", "lunhui-jian");

        prepare_skill("unarmed", "huntian-baojian");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "powerup" :),
        }));

    
        setup();
        carry_object("/d/wudang/obj/whiterobe")->wear();

}

// ����Ȥζ����
int ask_quest()
{       

        object  me;

    me = this_player();

    if ( mapp(me->query("xquest")))
        {
         message_vision(CYN "$N" CYN "����$n���˿���˵����������������������"
                            "Ҫ����ɲ��˾��Ⱥ���˵һ��ȡ������\n"NOR,
                        this_object(), me);
                        return 1;
        }

        if ( time() - me->query("xquest_last_cancel") < 60 )
        {
         message_vision(CYN "$N" CYN "����$n���˿���˵���������ȡ����һ������"
                            "�Ⱥȿ�ˮЪ����ٽ�������һ���ɡ���\n"NOR,
                        this_object(), me);
                        return 1;
        }


      message_vision(CYN "$N" CYN "����$n���˿������ͷ˵�����ܺã���Ȼ������"
                        "�������ұ�ָ����һ����·����\n"NOR,
                    this_object(), me);
      me->set("xquest/target_npc", "�������");
      call_other(XQUEST, "next_quest", me );  //����next_quest���������µ�����
      return 1;
}

//ȡ��Ȥζ����

int ask_cancel()
{       
      object    me,*obj;
      int i;

      me = this_player();

      if ( ! mapp(me->query("xquest")))
        {
         message_vision(CYN "$N" CYN "����$n���˿���˵����������û�и��"
                            "����û��������ȡ��ʲô����\n"NOR,
                        this_object(), me);
                        return 1;
        }

      if ( time() - me->query("xquest_total_cancel/time") > 3600 )
      {
         me->delete("xquest_total_cancel");
         me->set("xquest_total_cancel/time", time());
      }
      else
      {
         if ( me->query("xquest_total_cancel/total") >= 5 )
         {
            message_vision(CYN "$N" CYN "����$n���˿���˵������һСʱ��ֻ��"
                            "ȡ��������񣡡�\n"NOR,
                        this_object(), me);
                        return 1;
         }
      }

         message_vision(CYN "$N" CYN "����$n���˿���˵�������ţ�����ô���δ���"
                            "�Ǻ������ģ�\n�ؼ���Ҫ�������ٽ�����������������"
                            "�ĳɹ�����\n"NOR,
                            this_object(), me);

      if ( me->query("xquest/kind") == "do_drawing")   //����Ҫ���С����
        {
                obj = all_inventory(me);
                for(i=0; i<sizeof(obj); i++) 
                {       
                        if (base_name(obj[i]) == BAG)
                        {
                                destruct(obj[i]);
                                
                                message_vision(HIG "$N��$n˵��������Ȼ�㲻����˼ҵ�æ"
                                "�������С�����ҾͰ������ԭ���ˡ���\n"
                            "$N˵�žʹ�$n��������һ��С����\n"NOR,
                                this_object(),me );

                                break;
                        }  
                }       
         }

       tell_object(me, HIG"���Ȥζ����ȡ���ˡ����������ɣ�\n"NOR);

        if ( me->query("weiwang") > 10000 && me->query("score") > 10000 )
        {
           me->add("weiwang", -100);
           me->add("score", -100);

           tell_object(me, HIR"��������ͽ��������ܵ���һ����ʧ��\n"NOR);
        }
         me->delete("xquest");
         me->delete("xquest_count");
         me->set("xquest_last_cancel", time());

         me->add("xquest_total_cancel/total", 1);

        return 1;
}

int ask_mirror()
{       
    
      object me, ob, *obj;
      int i,have;
      me = this_player();
      have = 0;

      obj = all_inventory(me);
                for(i=0; i<sizeof(obj); i++) 
                {       
                        if (base_name(obj[i]) == MIRROR)
                        {
                  have = 1;
                        }  
         }

            if ( have == 1 )

            {
               message_vision(HIG "$N��$n˵�������������Ѿ���һ��������"
                                                  "��̰�����ᣡ��\n"NOR,
                                this_object(),me );
               return 1;
            }
            else
            {

           ob = new(MIRROR);
           ob->move(me);

       message_vision(HIG "$N����$n���˿���˵�������ţ����������ɵ����ã�\n"
                         "�ú�����������������ж����͹۲����ɡ���\n"NOR
                         CYN"$N�ӻ����ó�һ��Ǭ����������$n��\n"NOR,
                            this_object(), me);
              return 1;
            }

      return 1;

}

int ask_hulu()
{
    message_vision(HIG "$N����$n���˿���˵��������Ȼ���뿼��һ���Լ���"
                       "�����Ҿͳ�ȫ��ɡ���\n"NOR
                       CYN"ֻ��$N����һ�ӣ�$n��ʱ��ʧ����Ӱ���١�\n"NOR,
                       this_object(), this_player());
    this_player()->move(HULU_INSIDE);
    return 1;
}

void unconcious()
{
        die();
}
