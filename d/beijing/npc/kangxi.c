//�������

#include <ansi.h>
#define INVASIOND "/u/sanben/invasion/invasiond"

inherit NPC;
mixed ask_reward();

void create()
{
	set_name(HIY"�������"NOR, ({ "kangxi dadi", "kangxi", "dadi", "huang shang"}));
       set("title", HIC"��������"NOR );
	set("age", 32);
	set("gender", "����");
	set("long", "����ǵ���ʥ�Ͽ���������ǣ�һ����������֮�ࡣ\n");
	set("attitude", "peaceful");

	set("str", 30);
	set("dex", 30);
	set("combat_exp", 100000);
	set("shen_type", 1);

	set_skill("unarmed", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("sword", 100);
	set_skill("force", 100);
	set_temp("apply/attack", 100);
	set_temp("apply/defense", 100);
	set_temp("apply/damage", 60);
	set_temp("apply/armor", 60);

    set("inquiry", ([
           	"�ʹ�" : (: ask_reward :),
           	"����" : (: ask_reward :),
           	"����" : (: ask_reward :),
            "reward" : (: ask_reward :),
        ]));
	setup();
    carry_object("/d/beijing/npc/obj/longpao")->wear();
}

void init()
{
    object me = this_player();

    if ( userp(me) )
    {
      command("say �������˺�Ϊ��");
      add_action("do_answer","answer");
    }
}            


mixed ask_reward()

{
        object me;
        string *w, word, space;
        space = "                                            ";

        me = this_player();

        w = ({ "����", "��ǿ", "����", "ɱ��", "����", "Ϊ��",
               "�Ҿ�", "����", "����", "��ƶ", "����", "��ȡ", "��ʵ", "�ܽ�",
               "����", "����", "�Ƶ�", "��־", "��Т", "����", "����", "����",
               "����","��Ծ","��ǿ","����","�Ͻ�","����","����","����","�ؼ�",
               "����","����","����","��ҵ","��ʦ","�ص�","����","�Ի�","����",
               "����","����","����","ֱǰ","����","����","����","����","�Ž�",
               "����","����","����","����","����","ͼǿ","����","��","����",
               "��ϸ","����","����","�Ż�","����","����","��ս","��ʤ","����",
               "�ش�","����","����","����","�Ի�","�׺�","ɣ��","�۾�","����",
               "�ڴ�","����","����","��˳","����","�ܷ�","ͼǿ","�Ṧ","ΰ��",
               "��ʤ","����","�","�ط�","����","��ͼ","����","Я��","����",
               "�͸�","����","�Ͷ�","����","����","����","��ѧ","��ʵ","����",
               "����","�²�","����","��ǿ","����","����","�","�ط�","����",
               "Э��","��ͳ","����","����","��ò","ǫ��","����","����","��ҵ",
               "����","����","����","ǿ��","�ڷ�","��ѧ","��֪","�̿�","����",
               "����","����","����","ͦ��","��ǿ","����","Ϊ��","����","����",
               "����","Т˳","���","����","�Ͽ�","��ʵ","���","����","����",
               "�ȱ�","׷��","����","��˽","Ϊ��","Ϊ��","����","����","����",
               "Ӣ��","ǫ��","ƴ��","�Ϲ�","����","Ż��","��Ѫ","����","��ҵ",
               "����","����","���","����","�ҳ�","̹��","����","�԰�","�ڼ�",
               "����","����","�½�","ǫ��","����","��η","�ʵ�","̽��","ʵ��",
               "��ʵ","��Ծ","����","����","����","ͼǿ","����","����","����",
               "��","����","��ǿ","����","ɱ��","����","Ϊ��","�Ҿ�","����",
               "����","��ƶ","����","��ȡ","��ʵ","�ܽ�","����","����","�Ƶ�", 
               "��־","��Т","����","����","����", });
        word = w[random(sizeof(w))];

       if ( environment(this_object()) != find_object("/d/beijing/hg") )
          {
            command("say ���գ�����β��ڻʹ���");
            message_vision("$N����ææ���뿪�ˡ�\n", this_object());
            this_object()->move("/d/beijing/hg");
            return 1;
          }
        if ( ! find_object(INVASIOND) || ! INVASIOND->query("record") )
           return command("say ����ް˹���������ѽ��");
        if ( ! INVASIOND->query("record/all_killed") )
           return command("say �޲�δ��׼�ʹͣ�����������ȥ��");
        if ( me->query("waidi/born_time") != INVASIOND->query("record/born_time"))
           return command("say ��֮�ʹ��ѹ����ˣ�"); 


        command("say ԭ���ǿ����˹���������ʿ������������");
        command("say ��һ������ʶ�ı�������˫ȫ������־ʿ����λ" +
                RANK_D->query_respect(me) + "ɱ�����ͣ�������ճ��ڣ�\n"
                "              ������Ҫ��������֮�⣬��������Ĳ����Ρ�");
        command("say �㿴����д����������ʲô�֣�(����answer xxx ����)");
        if (! me->query_temp("upscreen"))
        {
           me->set_temp("upscreen",50);           
           for(int xx = 0; xx < 10; xx++)
           write("\n");        
        }
        me->set("waidi/word",word);
   
        write(ESC+"[r"+TOBOT(50));
     
        write(SAVEC);
        write(SETDISPLAY(7, 0) + DELLINE);
        write(SETDISPLAY(1, 0) + DELLINE);
        write(SETDISPLAY(2, 0) + DELLINE);
        write(SETDISPLAY(3, 0) + DELLINE);
        write(SETDISPLAY(4, 0) + DELLINE);
        write(SETDISPLAY(5, 0) + DELLINE);
        write(SETDISPLAY(6, 0) + DELLINE);


         write(SETDISPLAY(3, 20) + HIY"�������֮���"NOR );
         write(SETDISPLAY(5, 23) + HIW + word[0..1] + 
               "    " + word[2..3] + NOR);
         write(REST);
         write(TOBOT(50));        
        
         return 1;
}             

mixed do_answer(string arg)
{
    int pot,gn;
    string reward, unit;
    object me, ob, gold;

    string *ob_list = ({
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/linghui2",
                "/clone/fam/pill/linghui2",              
                "/clone/fam/pill/full1",
                "/clone/fam/pill/full1",
                "/clone/fam/pill/full1",
                "/clone/fam/pill/yulu",
                "/clone/fam/pill/neili2",
                "/clone/fam/pill/neili2",
                "/clone/fam/pill/neili2",
                "/clone/fam/pill/lingzhi4",
                "/clone/fam/etc/va1",
                "/clone/fam/etc/va2",
                "/clone/fam/etc/va3",
                "/clone/fam/etc/va4",
                "/clone/fam/etc/va5",
                "/clone/fam/etc/va6",
        }); 

    me = this_player();

    if (! me->query("waidi/word") )
    return command("say ��û�˸�������⣬���ʲô��");
    if ( ! find_object(INVASIOND) || ! INVASIOND->query("record") )
           return command("say ����ް˹���������ѽ��");
    if ( ! INVASIOND->query("record/all_killed") )
           return command("say �޲�δ��׼�ʹͣ�����������ȥ��");
    if ( me->query("waidi/born_time") != INVASIOND->query("record/born_time"))
    return command("say ��֮�ʹ��ѹ����ˣ�");

    if ( !arg )
    return command("say ��Ҫ�ش�ʲô?");

    if ( me->query("waidi/word") != arg )
    {
       command("say ��ϧ����λ" + RANK_D->query_respect(me) + "��Ȼ���ճ���,"
               "����Ŀ��ʶ�����޲��ܸ����ʹ��ˡ�");
       command("say �㻹��������ȥ�ɣ�");
       me->delete("waidi");
       return 1;
    }

    if ( me->query("waidi/word") == arg )
    {
      pot = 500 * me->query("waidi/number") + random(500);
      gn = me->query("waidi/number") + random(2);
      if (gn > 10) gn = 10;

      reward = ob_list[random(sizeof(ob_list))];
      ob = new(reward);
      if (ob->query("base_unit"))
                unit = ob->query("base_unit");
        else
                unit = ob->query("unit");
       gold = new("/clone/money/silver");
       gold->set_amount(gn);

     me->add("potential",pot);
     gold->move(me,1);
     ob->move(me,1);

     command("say ��������������λ" + RANK_D->query_respect(me) + "�������ճ���,"
              "�Ĳ����ǲ��ƣ���Ҫ�����ʹ����㡣");
   message( "invasion", HIR"��������֡�"NOR HIG"�����ܹ�[Danei zongguan]:ʥּ����\n"NOR
   HIY"            �����Ͽ��ͣ�\n"
   "            �Ϳ�����ʿ" + me->query("name") + "(" + me->query("id") + ")" +
   "Ǳ��" + chinese_number(pot) + "�㣬����" + chinese_number(gn) + "����" +
   ob->query("name") + NOR HIY"һ" + unit + "��\n"
            "                                         �մˣ�\n" NOR,users());

     me->delete("waidi");
     return 1;
    }

}

void unconcious()
{
        die();
}