//�޸��츳�������Ե�ʧ�ܼ�¼��NPC
//cracked by MIKE 2004.05.26
//last modified by MIKE 2004.06.19
#include <ansi.h>
#include <command.h>
inherit NPC;
string ask_zhongqiugift();
string ask_guoqinggift();

int do_addgift(string arg);
int ask_gift();
int do_add(string arg);
//int sub_gift();
//int do_subtract(string arg);
//int select_sp(string arg);

void create()
{
    set_name(HIC"С���"NOR, ({"xiao maike" }));
        set("title", ""HIR"��"HIG"����ʹ��"HIW"��"NOR""HIY"��"HIM"��"HIC"ʹ"HIG"��"NOR"");   
    set("gender", "����");
    set("age", 24);
    set("per", 70);
      set("str", 500000);
    set("int", 40);
    set("con", 40);
    set("dex", 40);
    set("qi",5000);
    set("jingli",5000);
    set("max_qi", 5000);
    set("max_jing", 5000);
    set("eff_jingli", 5000);
    set("jiali", 190);
    set("combat_exp", 5647645745754);
    set("shen", 25000);
   set("chat_chance", 10);
        set("chat_msg", ({
        "С������ĳ����������ǵ�����ʱ������\n",
        "С������ĳ������������Զ������Ļ�\n",
        "С������ĳ����������Ҿ����Ƿ紵���\n",
        "С������ĳ��������������޳�\n",
        "С������ĳ�����������ɣ�仯\n",
        "С������ĳ���������ЩΪ���������Ĵ���\n",
        "С������ĳ�����������Զ�������İ�\n",
        "С������ĳ��������������ĵĳ��ĵĻ�\n",
        "С������ĳ�������������������Ȼ��û����\n",
        "С������ĳ��������߰��߰�����Ҫѧ���Լ�����\n",
        "С������ĳ��������߰��߰��������⾭����ʹ����\n",
        "С������ĳ��������߰��߰�Ϊ�Լ�������һ����\n",
        "С������ĳ�������Ҳ����������\n",
        "С������ĳ�������Ҳ����Ȼ����\n",
        "С������ĳ����������ǰ��Ĵ���\n",
        "С������ĳ�������Ҳ����ż�����ǻ�����\n",
        "С������ĳ�������ż�������������\n",
        "С������ĳ��������͵����Ǹ������Ѱ�\n",
        "С������ĳ�������Ҳ��������Ҳ����ǣ��\n",
        "С������ĳ�������ֻ�������в����л�\n",
        "С������ĳ������������¶����ȥ��\n",
        "С������ĳ��������������ĵĳ��ĵĻ�\n",
        "С������ĳ�����������������\n",
        "С������ĳ���������Ȼ��û����\n",
        }));
        set("inquiry", ([
                "�츳": (: ask_gift :),        
                        "�������": (: ask_zhongqiugift :),
                        "�������": (: ask_guoqinggift :),

            //    "������¼": (: sub_gift :),
                //      "special":(:select_sp:),
        ]));

    setup();
}
void init()
{object me;
::init();
        add_action("do_addgift","addgift");
        add_action("do_add", "add");
       // add_action("do_subtract", "subtract");
        if( interactive(me = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
}
void greeting(object ob)
{object me;
me=this_player();
 if (!ob || !present(ob, environment())) return;
            write(HBRED"��ask xiao maike about �츳 ���޸�����츳�ɣ�\n"NOR);
         //   write(HBRED"��ask xiao maike about ������¼  �������Ե�ҩʧ�ܼ�¼�ɣ�\n"NOR);
            return ;
}
/*
int accept_object(object me, object ob)
{
        
        if (ob->query("money_id") && ob->value() >= 1000000) //��ʱǮ��λΪ10 gold���ų����޸ģ�����ʦ�����޸ģ�
        {
                tell_object(me, HIW "��ʹ��subtract ���Ե�Ӣ��ID�������룺substract int������\n" NOR);
                me->set_temp("givemike",1);
                return 1;
        }

        switch (random(2))
        {
        case 0:
                command("say Ǯ����Ŀ��������Ȼ����ң��Ҿ������ˣ�лл໣�");
                break;
        case 1:
                command("say Ǯ��Ŀ��������Ȼ���ˣ���û���ˣ�������");
                break;
        }
                        if (! ob->is_character())
        {
                destruct(ob);
                return -1;
        }
        return 1;

        }
int sub_gift()
{
        object me;
        me=this_player();
        
                 command("tell " + me->query("id") +
                        " ����ȸ�Ǯѽ��Ŀǰ������100GOLD�ɣ����Ǻܶ�ɣ�");
                return 1;
}
int do_subtract(string arg)
{               object me;
                me=this_player();
        if (!me->query_temp("givemike"))
        {
                command("say ���ʲô���񾭲� !");
                return 1;
        }

        if (! arg || ! stringp(arg))
        {
               command("shake " + me->query("id"));
               command("say ��ø�����Ҫ�����ĸ�����ѽ��" NOR);
                return 1;
        }     
        if (arg=="str")   
        {if(me->query("gift/str/fail")==0){
                command("tell " + me->query("id") +
                        " �������ʧ�ܼ�¼�Ѿ�Ϊ�㣬��������ѽ��Ǯû����\n");       
                me->set_temp("givemike",0);
                return 1;
                }
        me->add("gift/str/fail", -1);
command("tell " + me->query("id") +
                        " �������ʧ�ܼ�¼������һ��\n");       
                me->set_temp("givemike",0);
                         return 1;}
         if (arg=="int")   
        {if(me->query("gift/int/fail")==0){
                command("tell " + me->query("id") +
                        " �������ʧ�ܼ�¼�Ѿ�Ϊ�㣬��������ѽ��Ǯû����\n");       
                me->set_temp("givemike",0);
                return 1;
                }
         me->add("gift/int/fail", -1);
command("tell " + me->query("id") +
                        " �������ʧ�ܼ�¼������һ��\n");       
                me->set_temp("givemike",0);
                         return 1;}
if (arg=="con")   
        {if(me->query("gift/con/fail")==0){
                command("tell " + me->query("id") +
                        " ��ĸ���ʧ�ܼ�¼�Ѿ�Ϊ�㣬��������ѽ��Ǯû����\n");       
                me->set_temp("givemike",0);
                return 1;
                }
me->add("gift/con/fail", -1);
command("tell " + me->query("id") +
                        " ��ĸ���ʧ�ܼ�¼������һ��\n");       
                        me->set_temp("givemike",0);
                         return 1;}
if (arg=="dex")   
        { if(me->query("gift/dex/fail")==0){
                command("tell " + me->query("id") +
                        " �����ʧ�ܼ�¼�Ѿ�Ϊ�㣬��������ѽ��Ǯû����\n");       
                me->set_temp("givemike",0);
                return 1;
                }
me->add("gift/dex/fail", -1);

command("tell " + me->query("id") +
                        " �����ʧ�ܼ�¼������һ��\n");       
                        me->set_temp("givemike",0);
                         return 1;}

       return 1;
        }
        */
int ask_gift()
{
        object me;
        me=this_player();            
                 if (me->query("rmb")<2)
      {    command("tell " + me->query("id") +
                        " �㶼�޸Ĺ��ˣ������ʣ��ޣ���\n");   
      return 1;}  

        if (me->query("rmb")==20)
                me->add("rmb",-4);
        if (me->query("combat_exp") >= 0)
                        {command("tell " + me->query("id") +
                        " ������޸��츳��,��ʽΪadd str�Ϳ���ÿ�μ�һ�㣻��������Ӣ��ID���£�\n"
                          "�������� " HIG "str" HIY " �� "
                          "���ԣ��� " HIG "int" HIY " �� "
                          "���ǣ��� " HIG "con" HIY " �� "
                          "������ " HIG "dex" HIY " ��\n");
                me->set_temp("modified", 1);
                return 1;
         }
                 command("tell " + me->query("id") +
                        " ��ľ��鲻��ѽ���Ͻ����ɣ�");
                return 1;
}
int do_add(string arg)
{               int x=0;

                object me;
                me=this_player();
                x=(me->query("rmb"));
      if (x<2)
      {    command("tell " + me->query("id") +
                        " �����ʹ�õĴ���Ѿ�������\n");   
      return 1;}    



        if (!me->query_temp("modified"))
        {
                command("say ��˵ʲô��");
                return 1;
        }

        if (! arg || ! stringp(arg))
        {
               command("shake " + me->query("id"));
               command("say ��ø�����Ҫ���ĸ�����ѽ��" NOR);
                return 1;
        }     
        if (arg=="str")   
        {me->add("str", 1);
command("tell " + me->query("id") +
                        " �������������һ��\n");       
                        me->add("rmb", -2);
                         return 1;}
         if (arg=="int")   
        {me->add("int", 1);
command("tell " + me->query("id") +
                        " �������������һ��\n");       
                        me->add("rmb", -2);
                         return 1;}
if (arg=="con")   
        {me->add("con", 1);
command("tell " + me->query("id") +
                        " ��ĸ���������һ��\n");       
                        me->add("rmb", -2);
                         return 1;}
if (arg=="dex")   
        {me->add("dex", 1);
command("tell " + me->query("id") +
                        " �����������һ��\n");       
                        me->add("rmb", -2);
                         return 1;}

       return 1;
        }


int accept_kill()
{
        command("say ѽ�������ʲô��");
        return 1;
}

void unconcious()
{
        die();
}

void die()
{
        command("chat �����ˣ��������ˣ�");
        message_vision("$N��Ҳ�Ƶ������ˡ�\n", this_object());
        destruct(this_object());
}
string ask_zhongqiugift()
{
        object me;
        object gift;
    me=this_player();
//               if (me->query("/txwd/gift/zhongqiu2004"))
//      {    command("tell " + me->query("id") +
 //                       " ������֣�\n");   
 //     return 1;}  
              // �Ѿ���ȡ������
        if (me->query("/txwd/gift/zhongqiu2004"))
                 return HIR "��������֣���\n" NOR;
        
        // �Ѿ��Թ�����
        if (me->query("/txwd/gift/zhongqiu2004_eated"))
                 return HIR"��������֣���\n" NOR;

                        command("tell " + me->query("id") +
                        " ��л���ԡ������޵С���֧�֣�лл��\n");
        // ��������
        message_vision(HIY "С���Ц�����ض�$N˵������������֣���\n" NOR, me);
        command("smile");
        command("say �����Ҹ���һ���±��԰ɣ�");
        message_vision(HIY "С��ý��±�����$N" HIY "\n", me);        
        tell_object(me, HIG "��õ���һ���±���\n");
                                gift=new("/clone/gift/yuebing");
                                gift->move(me);
                me->set("/txwd/gift/zhongqiu2004", 1);
                return "�ٴθ�л����֧�֡�";
}
string ask_guoqinggift()
{
        object me;
        object gift;
    me=this_player();
              // �Ѿ��ʹ���
        if (me->query("/txwd/gift/guoqing2004"))
                 return HIR "������ڿ��֣���\n" NOR;
        

        // ��������
        message_vision(HIY "С���Ц�����ض�$N˵����������ڿ��֣���\n" NOR, me);
        command("smile");
        command("say �����Ҹ���4�����԰ɣ�");
        command("tell " + me->query("id") +
                        " ������޸��츳��,��ʽΪaddgift str�Ϳ���ÿ�μ�һ�㣻��������Ӣ��ID���£�\n"
                          "�������� " HIG "str" HIY " �� "
                          "���ԣ��� " HIG "int" HIY " �� "
                          "���ǣ��� " HIG "con" HIY " �� "
                          "������ " HIG "dex" HIY " ��\n");

                me->set("/txwd/gift/guoqing2004", 1);
                me->set_temp("guoqing",1);
                me->set("guoqingnumber",4);
                return "�ٴθ�л����֧�֡�";
}
int do_addgift(string arg)
{
                object me;
                me=this_player();
      if (me->query("guoqingnumber")<=0)
      {    command("tell " + me->query("id") +
                        " �����ʹ�õĹ�������Ѿ�������\n");   
      return 1;}    



        if (!me->query_temp("guoqing"))
        {
                command("say ��Ҫ��ʲô��");
                return 1;
        }

        if (! arg || ! stringp(arg))
        {
               command("shake " + me->query("id"));
               command("say ��ø�����Ҫ���ĸ�����ѽ��" NOR);
                return 1;
        }     
        if (arg=="str")   
        {me->add("str", 1);
command("tell " + me->query("id") +
                        " �������������һ��\n");       
                        me->add("guoqingnumber", -1);
                         return 1;}
         if (arg=="int")   
        {me->add("int", 1);
command("tell " + me->query("id") +
                        " �������������һ��\n");       
                        me->add("guoqingnumber", -1);
                         return 1;}
if (arg=="con")   
        {me->add("con", 1);
command("tell " + me->query("id") +
                        " ��ĸ���������һ��\n");       
                        me->add("guoqingnumber", -1);
                         return 1;}
if (arg=="dex")   
        {me->add("dex", 1);
command("tell " + me->query("id") +
                        " �����������һ��\n");       
                        me->add("guoqingnumber", -1);
                         return 1;}

       return 1;
        }

