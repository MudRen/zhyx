#include <ansi.h>
#define QUESTKILL_D    "/quest/questkh/quest/questkill"
#define QUESTKH_D(x)   ("/quest/questkh/quest/questkh" + x)
#define KHMSG_D      ("/quest/questkh/kuihua-msg")

inherit NPC;

void greeting(object);
void init();
int give_quest();
int give_up();
void destory(object);
void npc_dest(object);
string time_period(int timep);

void create()
{
   set_name(HIR"����̫��"NOR, ({ "dongfang bubai", "dongfang", "bubai" }));
   set("gender", "����");
   set("age", 52);

   set("str", 20);
   set("dex", 30);
   set("per",19);
    set("con",3000);

   set("long",
"�����������������ڰ���������֮ɫ��\n"
"��ħ�̽�����������һϮ��������ϱ�ʩ֬\n"
"�ۣ�����������ɫ����������һ���廨���ܣ�\n"
"���ֳ���һö�廨�룬������ԧ��Ϸˮ����\n"
"����һ�롣\n");
   set("combat_exp", 24000000);
   set("shen_type", -1);
   set("attitude", "heroism");
   set_skill("unarmed", 100);
   set_skill("force", 500);
   set_skill("sword", 500);
   set_skill("dodge", 500);
   set_skill("parry", 500);
   set_skill("pixie-jian", 500);
   map_skill("dodge","pixie-jian"); 
   map_skill("parry","pixie-jian");
   map_skill("sword","pixie-jian"); 

   set("inquiry", ([
          "����" : "�������ܵ���ͷ��һ��һ�ߣ�ȫ���ע����������\n",
    ]) );

    set("qi",9900000);
    set("max_qi",9900000);
    set("jing",9900000);
    set("max_jing",9900000);
    set("neili",900000);
    set("max_neili",900000);
    set("jingli",900000);
    set("max_jingli",900000);
   setup();
}

void init()
{
   object ob;

   ::init();

   if( interactive(ob = this_player()) && query("kill_all") )
   {
      call_out("greeting", 2, ob);
   }
   add_action("give_quest", "quest");
   add_action("give_up","giveup");
}

int give_quest()
{
    mapping questtemp,questkh,questkill,skills;
    object ob,npc;
    int exp,time,level,i,lev,lev1;
    string msg,*sname,place;
        
    ob = this_player();
    exp = (int)ob->query("combat_exp");

    if( (ob->query("character") != "���ռ�թ") && (ob->query("character") != "�ĺ�����"))  
    {
        message_vision("����̫��̧ͷ����$Nһ�ۣ�����ɤ�ӵ���������ż��ʼ���Ļ�ɫ���ٲ����ϸ��ҹ�����������Ѫ���岽����\n", ob);
        return 1;
    }
    if( ob->query("shen") >= 0)  
    {
        write("����̫��ͷҲ��̧������̾�˿������������ú�һ���ˣ�ƫҪ����Ͷ���������ҵ������������ǲ����������\n");
        return 1;
    }
    if(exp < 1000)
    {
        write("����̫��ͷҲ��̧���������������ȥ��������ɣ���Ϊ�����£��㻹�����ء���\n");
        return 1;
    }
    if (mapp(ob->query("quest_kh")))
    {
       write("����̫����������й��棬΢΢��ͷ��������������ͷ�������������ˣ���\n");
        return 0;
    }
    if (mapp(ob->query("quest_ws")))
    {
        ob->delete_temp("questws_times");
        ob->delete("quest_ws");
    }

    if((time()-ob->query_temp("questkh_giveup_time")) < (2+random(2)))
    {
        write("��Ҫ������һ���\n");
        return 1;
    }

    if(exp <= 5000)         level = 0;
    else if(exp <= 22000)   level = 1;
    else if(exp <= 72000)   level = 2;
    else if(exp <= 170000)  level = 3;
    else if(exp <= 410000)  level = 4-random(2);
    else if(exp <= 800000)  level = 5-random(3);
    else if(exp <= 1500000) level = 6-random(3);
    else
    {
        if(random(6)==0||(exp>10000000&&random(3)==0))
            level = 8;                  //8����ר��ɱclone NPC������
        else
            level = 7-random(3);
    }

    i = ob->query_temp("questkh_times");
   
    if(i > 15 && random(20) > 15 || wizardp(ob))
    {
        questkill = QUESTKILL_D->query_questkill();
        msg = questkill["msg"];
        write("����̫�����۽������һ�ۣ�΢¶��ɫ���������㵹�Ǻ���ͦ�ܸɵ���ţ���\n");
        write(msg+"\n");
        time = questkill["time"]/2+random(questkill["time"]/2);
        write("����̫���ͷ���˿��㣬�ֵ������Ҹ���"+time_period(time)+"ʱ�䣬���ȥ�ա���\n");
        time += time();
      //��Ҫֱ���޸�questkill
        questkh = ([
            "name" :  questkill["name"], 
            "khmsg":  msg, 
            "dir"  :  questkill["dir"], 
            "type" :  questkill["type"], 
            "time" :  time,
            "level":  level,
            "desc" :  "��",
            ]),
        ob->set("quest_kh",questkh);
        return 1;
    }
    else
    {
        if(level==8)
        {
            npc = new(CLASS_D("generate") + "/killed.c");
            NPC_D->place_npc(npc, ob->query("combat_exp") < 500000  ? ({ "����һ��", "����ɽ", "����", "����" }) :
                                  ob->query("combat_exp") < 800000 ? ({ "����һ��", "����ɽ", "����" }) : ({"����"}));
            NPC_D->set_from_me(npc, ob, 100);
            npc->add_temp("apply/attack", npc->query_skill("force") * (level - 1) / 15);
            npc->add_temp("apply/dodge", npc->query_skill("force") * (level - 1) / 15);
            npc->add_temp("apply/parry", npc->query_skill("force") * (level - 1) / 15);
            npc->add_temp("apply/damage", 5 + level * 7);
            npc->add_temp("apply/unarmed_damage", 5 + level * 7);
            npc->add_temp("apply/armor", 10 + level * 15);
            npc->set_temp("quester", ob->query("id"));
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            place = npc->query("place");

            npc->set("shen", npc->query("combat_exp") / 2000);
            msg="����̫��޺޵�˵����"+npc->name(1)+
                "�����ν�Ĵ����Ŵκ������ԣ���˵�������" + 
                place + "����ȥ����������ͷ��������\n";

            questkh = ([
                "name" : npc->name(1),
                "id"   : npc->query("id"),
                "bonus": (100+random(41)),
                "type" :"ɱ",
                "level":8,
                "chinese_w":place,
                "where":npc->query("startroom"),
                "khmsg":msg,
            ]);
            tell_object(ob,questkh["khmsg"]+"\n");
            ob->set("quest_kh",questkh);

            return 1;       
        }
        else
            {
                questtemp = QUESTKH_D(level)->query_questkh(ob);
                if(undefinedp(msg = questtemp["msg"]) || msg == "" || random(2))
                {
                                if(questtemp["race"])
                                        msg=KHMSG_D->query_khmsg("��",questtemp["name"]);
                                else
                                        msg=KHMSG_D->query_khmsg(questtemp["type"],questtemp["name"]);
                        }
                questkh=([
                        "id":questtemp["id"],
                        "name":questtemp["name"],
                        "bonus":questtemp["bonus"],
                        "type":questtemp["type"],
                        "khmsg":msg,
                        "level":level,
                        ]);
                write(questkh["khmsg"]+"\n");
                ob->set("quest_kh",questkh);
            }
    }  
    return 1;
}

int accept_object(object who, object ob)
{
   int exp, pot,level,bonus,i;
   mapping questkh;
   object me,gold;
   int shen,mar,weiwang,score,quest_count;
   string msg;
   mixed special;
        
   me = this_object();
   if(!(questkh =  who->query("quest_kh")) ||
      (questkh["type"] != "Ѱ" && questkh["type"] != "ɱ"))
   {
      return notify_fail("����̫���������ͷ��ĳ���˵�����߿�����Ҫ�����ҡ���\n");
   }
   switch(questkh["type"])
   {
      case "Ѱ"  :
         if(ob->name(1) != questkh["name"] || userp(ob))
         {
            tell_object(who,"����̫���ŭ�������������ʲô��������������Ū��ô����\n");
            return notify_fail("����̫�����˿���������˦˦�֣���������ȥ�ɣ���Ҫ���ҡ���\n");
         }
         break ;
      case "ɱ"  :
         if(!ob->is_head() && !ob->is_corpse())
         {
            tell_object(who,"����̫��б���۾�����һ�£�����������Ǹ�ʲô��������������Ū��ô����\n");
            return notify_fail("����̫�������һ�ۣ�˦˦�֣��������㻹վ�������ʲô��������ȥ����\n");
         }
         else if (! stringp(ob->query("owner_id")) || ob->query("owner_id") != questkh["id"])
            {
                tell_object(who,"����̫�����ű��ӻ���˵������ʲô�����ģ���������ߣ���\n");
                return notify_fail("����̫�������һ�ۣ�˦˦�֣��������Ҹ�����������Ƿ������ˣ���\n");
            }
            else if(ob->query("killed_by") != who->query("id"))
            {
                tell_object(who,"����̫�����һ�����������Ǵ���������ģ����Լ�������ô����\n");
                return notify_fail("����̫�������һ�ۣ�˦˦�֣��������㻹վ�������ʲô���������ȥ����\n");
             }
         break ;
      default    :   
         return 0;
   }
   message_vision("$N��$n��������̫�ࡣ\n",who,ob);
   tell_object(who,"����̫����Ц��һ����̧ͷ���˿��㣬��ͷ�������ţ������ȥ�ˡ���\n");
   if((i=who->query_temp("questkh_times")) < 2)   i =10-i;
   else i = 1;
   level = questkh["level"]+1;
   exp = level*questkh["bonus"]*12/(i*(10+random(10)));
   pot = level*questkh["bonus"]/(3+random(5));

   score = random(exp/20);
   weiwang = random(exp/15);

   if (who->query_temp("questkh_times") + 1 > 200)
	mar = exp/5 + random(who->query_temp("questkh_times"));
   else mar = random(20);

   if(!random(18))
   {
      i=(exp/100+1);
      if(i>20) i=20;
      gold=new("/clone/money/gold");
      gold->set_amount(i);
      tell_object(who,"ͻȻһ���ƽ����������У��������̫������˵��������Щ������ȥ���պ���������㣡��\n"
          HIW"\n�㱻������ "+i+" ���ƽ�\n"NOR);
       if(!gold->move(who))
       {
          message_vision("����$N���϶���̫�أ��ƽ�һ���Ӵ����л����˵��ϡ�\n",who);
          gold->move(environment());
      }
      QUEST_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar, 
                            "weiwang" : weiwang, "score" : score, "percent" : 50 ]), 1);
   }
   else QUEST_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                              "weiwang" : weiwang, "score" : score ]), 1);
   
   quest_count = who->query_temp("questkh_times") + 1;
   if (quest_count == 100)
   {
       msg = "$N�ٺ���Ц������������С�ӻ����ԣ������ϰ�"
       "��������ɵĸɾ������������е�ǰ;����\n";
	special = 1;
	   } else
       if (quest_count == 200)
   { 
       msg = "$Ņͷʹ��������һ�۵��������ǲ�������"
       "������ɵû����׵�����\n";
       special = "/d/shaolin/obj/puti-zi";
   } else
       if (quest_count == 500)
   {
       msg = "$N̾���������ǳ���������ǰ�ˣ��벻����������"
       "��������һ��©�����ף����ף���\n";
       special = "/clone/misc/tianxiang";
   } else
       if (quest_count == 1000)
   {
       msg = "$N����̾�˿������������벻����������ǧ��"
       "������һʧ�֣������Ժ�Ľ��������������������\n";
       special = "/clone/gift/jiuzhuan";
   } else
       if ((quest_count % 10) == 0)
   {
       msg = "$N΢΢��ͷ�����ɵĲ�����Ȼ����" +
       chinese_number(quest_count) +
       "�ζ�û��ʧ�֣��������Һúñ��֣���\n";
   }
   if (special) {
       message_vision(msg, me, who);
       QUEST_D->special_bonus(me, who, special);
   }
   who->add_temp("questkh_times",1);
   who->delete("quest_kh");
   return 1;
}

int give_up()
{
   object ob,obj,room;
   mapping questkh;

   ob = this_player();

   if(query("kill_all"))   return 0;

   if(mapp(questkh =  ob->query("quest_kh")))
   {
      if(questkh["desc"] == "��")
      {
         message_vision("$N�ľ���ս��˫���Ҳ����������̫��ȡ���Լ�������\n",ob);
         message_vision("����̫�࿴��$Nһ�ۣ����š���һ�������ÿɷ�\n", ob);
      }
      else if(questkh["type"] == "ɱ"&&questkh["level"] == 8)    //by llm
      {
          message_vision("$N�ľ���ս��˫���Ҳ����������̫��ȡ���Լ�������\n",ob);
          message_vision("����̫��ͷҲ��̧������һ��������û�õĶ��������ģ���\n", ob);
          if(!(room = find_object(questkh["where"])) )
              room = load_object(questkh["where"]);

          if(objectp(obj = present(questkh["id"],room))
              &&obj->is_character()
              &&!userp(obj))
          {
              message_vision("$N����һ����ת���߿��ˡ�\n",obj);
              obj->move("/d/register/prison");
              destruct(obj);
          }
          ob->set_temp("questkh_times",0);
      }
      else
      {
         message_vision("$N�ľ���ս��˫���Ҳ����������̫��ȡ���Լ�������\n",ob);
         message_vision("����̫��ͷҲ��̧������һ��������û�õĶ��������ģ���\n", ob);
         ob->set_temp("questkh_times",0);
      }
   }
   else
   {
      message_vision("$N�ľ���ս��˫���Ҳ����������̫��ȡ���Լ�������\n",ob);
      message_vision("����̫��ר�İ������еĹŶ����������û����$N\n", ob);
   }
   ob->delete("quest_kh");
   ob->set_temp("questkh_giveup_time",time());
   return 1;
}

string time_period(int timep)
{
   int t, d, h, m, s;
   string time;
   t = timep;
   s = t % 60;             t /= 60;
   m = t % 60;             t /= 60;
   h = t % 24;             t /= 24;
   d = t;
 
   if(d) time = chinese_number(d) + "��";
   else time = "";
 
   if(h) time += chinese_number(h) + "Сʱ";
   if(m) time += chinese_number(m) + "��";
   time += chinese_number(s) + "��";
   return time;
}

void npc_dest(object npc)
{
    if(!npc) return;
    if(npc->is_fighting()&&npc->query_temp("wait_times")<4)
    {
        npc->add_temp("wait_times",1);   //4�λ���
        call_out("npc_dest",60,npc);     //�ٵ�һ����
        return;
    }
    if(npc->is_character())
        message_vision("$N����һЦ��������̫������¾���һЩ���ҷϣ���ת��һ�Σ��Ѳ�������Ӱ��\n",npc);
    npc->move("/d/register/prison");
    destruct(npc);
    return ;
}

