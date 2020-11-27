inherit NPC;
#include <ansi.h>
#define QUESTGOODS_D(x)    ("/quest/questdg/quest/questgoods" + x)
#define QUESTDG_D(x)      ("/quest/questdg/quest/questdg" + x)
#define DGMSG_D      ("/quest/questdg/dugu-msg")

void greeting(object);
void init();
int give_quest();
int give_up();
void npc_dest(object);
void destory(object);
string time_period(int);

string* dg_msg = ({
"�������Ц�Ǻǵ�˵����",
"��������������ŷ���������",
"������ܵ�ͷ�����룬˵������",
"������������ڴ���˵������",
"�������΢Ц�ŵ�����",
});

void create()
{
   set_name(HIW"�������"NOR, ({ "dugu qiubai", "dugu", "qiubai" }));
   set("gender", "����");
   set("age", 100);
   set("str", 50);
    set("dex", 50);
   set("per",20);
    set("con",3000);

   set("long",
"����һ������ͨͨ�����ߣ�һϮ�ֲ����ѣ�\n"
"���һ�ư��룬������͡�Ŀ��ת��֮�䣬\n"
"������¶��һ˿����֮����\n");
set("combat_exp",15000000);

   set("inquiry", ([
          "����" : "�������̾�˿�������������񽭺���Σ���ķ�����������ʿ���кܶ�����Ҫȥ��������\n",
    ]) );

    set("qi",9900000);
    set("max_qi",9900000);
    set("jing",9900000);
    set("max_jing",9900000);
    set("neili",9000000);
    set("max_neili",9000000);
    set("jingli",9000000);
    set("max_jingli",9000000);
   setup();
    carry_object("/clone/weapon/changjian")->wield();
    carry_object("/clone/misc/cloth")->wear();
}

void init()
{
   object ob;

   ::init();

   if( interactive(ob = this_player()) && !is_fighting() )
   {
      remove_call_out("greeting");
      call_out("greeting", 2, ob);
   }        
   add_action("give_quest", "quest");
   add_action("give_up","giveup");
}

void greeting(object ob)
{

   if( !ob || environment(ob) != environment() ) return;
   if( ob->query("quest_dg"))
   {
        write("������ܶ���΢΢һЦ����������������Ѿ�������𣿡�\n");
      return;
   }
}

int give_quest()
{
    mapping questtemp,questgoods,questdg,skills;
    object ob,npc,thing;
    int exp,time,bonus,level,i,lev,lev1;
    string msg,dest,error,dgmsg,place;
        
    ob = this_player();
    exp = (int)ob->query("combat_exp");

    if( (ob->query("character") != "��������") && (ob->query("character") != "������"))  
    {
        write("������ܿ�����һ�ۣ��������㱾��ɱ��̫�أ����ҵ��ദ�վñ�Ȼ����룬�㻹����������ȥ�ɣ���\n");
        return 1;
    }
    if( ob->query("shen") < 0)  
    {
        write("������ܶ����������������ͬ������Ϊı���㻹�����գ���\n");
        return 1;
    }
    if(exp < 1000)
    {
       write("������ܿ��˿��㣬�ḧ���룬�����������ն��㻹�������û������ɡ���\n");
        return 1;
    }
 
    if (mapp(ob->query("quest_dg")))
    {
        write("���������������ļ�򣬺Ǻ�Ц��������Ҫ�����Ƚ���ͷ��������˵����\n");
        return 0;
    }
    if (mapp(ob->query("quest_hs")))
    {
        ob->delete("quest_hs");
        ob->delete_temp("quesths_times");
    }
   
    if((time()-ob->query_temp("questdg_giveup_time")) < 2)
    {
        write("��Ҫ������һ���\n");
        return 1;
    }
    if(random(4)+1)
    {
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
if(wizardp(ob)) level = 0;
        questtemp = QUESTDG_D(level)->query_questdg(ob);
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
            npc->set("shen", -npc->query("combat_exp") / 2000);
            
            msg="���������ɫ���ص�����"+npc->name(1)+
                "��Ȼ�����ֽ���������ȥ������һ����\n���˿��ܻ���"+
                place+"���������˾��Ҳ����ˡ���\n",

            questtemp = ([
                "name" : npc->name(1),
                "id"   : npc->query("id"),
                "bonus": (100+random(41)),
                "type" :"ɱ",
                "level":level,
                "chinese_w":place,
                "where":npc->query("startroom"),
                "dgmsg":msg,
            ]);
            tell_object(ob,questtemp["dgmsg"]+"\n");
            ob->set("quest_dg",questtemp);

            return 1;
        }
        else
        {
                switch(questtemp["type"])
                {
                case "ɱ":
                        if(undefinedp(msg = questtemp["msg1"])||msg==""||random(2))
                        {
                                if(questtemp["race"])
                                        msg=DGMSG_D->query_dgmsg("��",questtemp["name"]);
                                else
                                        msg=DGMSG_D->query_dgmsg("ɱ",questtemp["name"]);
                        }
                        break;
                case "Ѱ":
                        if(undefinedp(msg = questtemp["msg"])||msg==""||random(2))
                                msg=DGMSG_D->query_dgmsg("Ѱ",questtemp["name"]);
                        break;
                case "��":
                        if(undefinedp(msg = questtemp["msg2"])||msg==""||random(2))
                        {
                                if(questtemp["race"])
                                        msg=DGMSG_D->query_dgmsg("׽",questtemp["name"]);
                                else
                                        msg=DGMSG_D->query_dgmsg("��",questtemp["name"]);
                        }
                        break;
                case "��":
                        npc = new(CLASS_D("generate") + "/dg_receiver.c");
                        NPC_D->place_npc(npc, ob->query("combat_exp") < 500000  ? ({ "����һ��", "����ɽ", "����", "����" }) :
                                              ob->query("combat_exp") < 800000 ? ({ "����һ��", "����ɽ", "����" }) : ({"����"}));
                        NPC_D->set_from_me(npc, ob, 100);
                        npc->set_temp("quester", ob->query("id"));
                        NPC_D->random_move(npc);
                        NPC_D->random_move(npc);
                        NPC_D->random_move(npc);
                        place = npc->query("place");
                        thing = new(questtemp["object"]);
                        thing->set("send_to",npc->query("id"));
                        thing->set("send_from",query("id"));
                        thing->set("send_from_name",query("name"));
                        msg = dg_msg[random(5)]+"�鷳����ҽ�"+thing->name(1)+"����"+npc->name(1)+"����"
                                                "����������"+place+"������ʱ�������ܾ��뿪�ˡ�";
                        if (!thing->move(ob))
                        {
                                thing->move(environment());
                                message_vision("������ܽ�$N������ڵ��ϡ�\n",thing);
                         } else message_vision("������ܽ�$N����$n��\n",thing,ob);
                         break;
                }
                questdg=([
                         "name":questtemp["name"],
                         "type":questtemp["type"],
                         "bonus":questtemp["bonus"],
                         "dgmsg":msg,
                ]);
        }
    }  
    tell_object(ob,questdg["dgmsg"]+"\n");
    questdg["level"]=level;
    ob->set("quest_dg",questdg);
    return 1;
}

int accept_object(object who, object ob)
{
   int exp, pot,level,bonus,time,times,i,quest_count,mar,score,weiwang;
   mapping questdg;
   string dest,msg;
   object gold;
   mixed special = 0;
        
   if(!(questdg =  who->query("quest_dg")) ||
      (questdg["type"] != "Ѱ" && questdg["type"] != "��" && questdg["type"] != "��"))
   {
      tell_object(who,"������ܿ��˿��㣬�ƺ���֪������ʲô��˼��\n");
      return notify_fail("������ܵ���һЦ���������ҿɲ�ȱʲô��������\n");
   }

   if( ob->name(1) != questdg["name"] || userp(ob))
   {
      tell_object(who,"�������̾�˿����������Ⲣ��������Ҫ�ġ�\n");
      return notify_fail("������ܿ����㣬���������ǲ�����ȥ���ҿ�������\n");
   }

   if(questdg["type"]=="��")
   {
      if (!ob->is_receipt() || ob->query("reply_to") != this_object()->query("id"))
      {
          write("������ܽӹ���һ�������ȵ�˵�����Ҳ��ǽ�������Ͷ�����ô�����ǲ��ǼǴ��ˣ���\n");
          return 0;
      }
   } 

   message_vision("$N��$n����������ܡ�\n",who,ob);
   tell_object(who,"������ܵ�ͷ΢Ц��������Ϊ��������������������\n");
   who->delete("quest_dg");
   destruct(ob);

   level = questdg["level"]+1;
   if((i=who->query_temp("questdg_times")) < 2)   i =10-i;
   else i = 1;
   if(who->query_temp("questdg_times")< 2)   
       exp=level*5+random((9-level)*(9-level))/2;
   else
       exp = level*questdg["bonus"]*156/(10*i*(10+random(5)));
   
   pot = exp/(3+random(3));
   score = random(exp/20);
   weiwang = random(exp/15);

   if (who->query_temp("questkh_times") + 1 > 200)
	mar = exp/5 + random(who->query_temp("questkh_times"));
   else mar = random(20);
   
   if(wizardp(who)||!random(10))
   {
      i=(exp/100+1);
      if(i>20) i=20;
       gold=new("/clone/money/gold");
       gold->set_amount(i);
       tell_object(who,"����˵�������������߽�������ͷ�е���ɣ��������õ�ƽ����̲��ɣ���\n"
          HIW"\n�㱻������ "+i+" ���ƽ�\n");
       if(!gold->move(who))
       {
           message_vision("����$N���϶���̫�أ��ƽ�һ���ӵ����˵��ϡ�\n",who);
           gold->move(environment());
       }
       QUEST_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                             "weiwang" : weiwang, "score" : score, "percent" : 50 ]), 1);
   }
   else QUEST_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                              "weiwang" : weiwang, "score" : score ]), 1);

   who->add_temp("questdg_times",1);

   quest_count = who->query_temp("questdg_times");
   if (quest_count == 100)
   {
       msg = "$N���˵ķ�����Ц�������ӿɽ̣������ϰ�"
       "��������ɵ�ƽƽ���ȣ�����Ŭ������\n";
	special = 1;
	   } else
       if (quest_count == 200)
   { 
       msg = "$NЦ�ĺϲ�£�죬�������ͷ������������������"
       "������ɵ�ƯƯ��������\n";
       special = "/d/shaolin/obj/puti-zi";
   } else
       if (quest_count == 500)
   {
       msg = "$N������ѣ������򵥣����ǲ��򵥣���������"
       "��������һ��©����ţ���Ű�����\n";
       special = "/clone/misc/tianxiang";
   } else
       if (quest_count == 1000)
   {
       msg = "$N����������˵��������Ȼ������ǧ��"
       "������һʧ�֣����ǰ�����������Ű�����\n";
       special = "/clone/gift/jiuzhuan";
   } else
       if ((quest_count % 10) == 0)
   {
       msg = "$N�Ǻ�Ц�ţ�������ֺܲ�������Ȼ����" +
       chinese_number(quest_count) +
       "�ζ�û��ʧ�֣���æ����������������\n";
   }
   if (special) {
       message_vision(msg, this_object(), who);
       QUEST_D->special_bonus(this_object(), who, special);
   }
   return 1;
}

int give_up()
{
    object ob,obj,room;
    mapping questdg;

    ob = this_player();

    if(mapp(questdg =  ob->query("quest_dg")))
    {
        write("�������߲ѣ�����������ȡ���Լ�������\n");
        write("������ܺ�����ɫ����������Դ���������û��ϵ��Ҫ����Ŭ��������\n");
        if(questdg["type"] == "��")
        {
            if(objectp(obj = questdg["obj"]))
            {
                if(obj->is_character())
                    message_vision("$NһԾ�����ܵ���Ӱ�����ˡ�\n",obj);
                obj->move(environment(ob));
                destruct(obj);
                if(ob->query_temp("questdg_times") > 0)
                    ob->add_temp("questdg_times",-1);
            }
        }
        else if(questdg["type"] == "ɱ"&&questdg["level"] == 8)    //by llm
        {
            if(!(room = find_object(questdg["where"])) )
                room = load_object(questdg["where"]);

            if(objectp(obj = present(questdg["id"],room))
                &&obj->is_character()
                &&!userp(obj))
            {
                message_vision("$N����һ����ת���߿��ˡ�\n",obj);
                obj->move("/d/wizard/prison");
                destruct(obj);
            }
            ob->set_temp("questdg_times",0);
        }
        else
            ob->set_temp("questdg_times",0);
    }
    else
        write("������ܺ�����ɫ�ؿ����㣬������û��ϵ�������ڸ�����û�����񰡣���\n");
    ob->delete("quest_dg");
    ob->set_temp("questdg_giveup_time",time());
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

void destory(object ob)
{
   if(!ob)
      return;
   if(ob->is_character())
      message_vision("$NһԾ�����ܵ���Ӱ�����ˡ�\n",ob);
   ob->move("/d/wizard/prison");
   destruct(ob);
   return ;
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
        message_vision("$N���صغ���һ�������������ǵ�С����ת��һ�Σ��Ѳ�������Ӱ��\n",npc);
    npc->move("/d/wizard/prison");
    destruct(npc);
    return ;
}
