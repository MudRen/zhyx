// ����ʦ

#include <ansi.h>

inherit NPC;
inherit F_SAVE;

#define WIZLEVEL 4 // �ܹ�������ִ����������ʦ�ȼ�
#define DISTANCE 5 // �����м����ʱ�䣨������

string query_save_file();
int do_start(string arg);
int do_paimai(string arg);
int begin_paimai();
int stop_paimai();
int do_jupai(object buyer,string arg);
int go_jupai();
int do_qiao(object me);
int do_paimailist(object me);
int do_unwelcome(string arg);
int finish_paimai(object me);
void heart_beat();
object check_operator();
int do_autopaimai(object me);

int last_time;		//���һ���ֹ�������ʱ��
object operator;

void create()
{
        seteuid(getuid());
        restore();

        set_name("��������", ({ "fujia tianxia", "fujia", "tianxia" }) );
        set("nickname", HIY+BLINK "���µ�һ��" NOR);
        set("channel_id","��������");
        set("gender", "����");
        set("age", 45);
        set("no_get", 1);
        set("long",
                "����һλ΢�ֿ���������ˣ��ݴ�����ĩ�յ�������ҵ���������ĺ��ֲ��ݡ�\n");
        set("combat_exp",600000);
        set("shen", 0);
        set("attitude", "friendly");

        set("apply/attack", 100);
        set("apply/defense", 100);

        set("max_qi", 800);
        set("qi", 800);
        set("max_jing", 800);
        set("jing", 800);
        set("max_jingli", 800);
        set("jingli",800);
        set("max_neili", 8000);
        set("neili",8000);
        
        set_skill("force", 300);
        set_skill("unarmed", 300);
        set_skill("sword",300);
        set_skill("parry",300);
        set_skill("dodge", 300);

        setup();

        carry_object("/clone/cloth/cloth")->wear();
}


void init()
{
        ::init();
        if (wiz_level(this_player()) >= WIZLEVEL)
        {
                add_action("do_paimai", "paimai");
                add_action("do_start","start");
                add_action("do_qiao","qiao");
                add_action("do_unwelcome","unwelcome");
                add_action("finish_paimai","finish");
                add_action("do_autopaimai","autopaimai");
        }

        add_action("do_paimailist", "paimailist");
        add_action("do_jupai", "jupai");
}

// �����ĵ�
string query_save_file()
{
        return "/data/npc/fujiatianxia";
}

int do_start(string arg)
{
        object ob,me;
        int i;
        string *heidian_list,msg;
        mapping *all_heidian;
        mapping begin_heidian;
        mapping end_heidian;

        me = this_player();
        ob = this_object();

        if (ob->query("paimai_start") && !ob->query("paimai_end"))
                return notify_fail("�������������У��޷����¿�ʼ��\n");

        if (!HEIDIAN_D->is_chushihua())
        {
                msg = "�ڵ���δȫ����ʼ�����ڽ�������֮ǰ�������Ƚ������кڵ�ĳ�ʼ����\n";
                msg += "��ʼ���ڵ��ָ�cshshop [�ڵ�ID]�������ʹ�ò�������ʾ��ʼ�����кڵꡣ\n";
                write(msg);
                return 1;
        } else
        {
                heidian_list = ({});
                begin_heidian = ([]);
                end_heidian = ([]);
                all_heidian = HEIDIAN_D->query_heidian();
                msg = HIC "�ɹ���ʼ���������򣬴������ڵ��б� \n" NOR;
                msg += HIC "--------------------------------------\n" NOR;
                for (i = 0;i < sizeof(all_heidian);i++)
                {
                        heidian_list += ({ all_heidian[i]["id"] });
                        begin_heidian[all_heidian[i]["id"]] = all_heidian[i]["price"];
                        msg += sprintf(HIY "%s" HIW "\t%s\n" NOR,all_heidian[i]["id"],all_heidian[i]["price"]);
                }
                msg += HIC "--------------------------------------\n" NOR;
                msg += HIC "�ܹ�" + HIW + chinese_number(sizeof(all_heidian)) + HIC + "�Һڵꡣ\n";

                ob->delete("owner");
                ob->delete("heidian_list");
                ob->delete("begin_heidian");
                ob->delete("end_heidian");
                ob->delete("paimai_end");
                ob->delete("now_paimai");
                ob->delete("temp_owner");
                ob->delete("wait_jupai");
                ob->delete("on_jupai");
                ob->delete("can_finish");

                ob->set("paimai_start",1);
                ob->set("heidian_list",heidian_list);
                ob->set("begin_heidian",begin_heidian);
                ob->set("end_heidian",end_heidian);

                if (arg) {
                        CHANNEL_D->do_channel( ob, "sys", "�ڵ�����ϵͳ��" + me->name(1) + "�ɹ�����������ģʽ���Զ���");
                        ob->set("operator","fujia tianxia");		//��������Ϊ�Զ�����
                        msg += HIR "��ѡ����ͨ���Զ����еķ�ʽ�������������̡�\n";
                        write(msg);
                        message_vision("$N�ֺǺǵĶԴ��˵��������������������֣��������ǾͿ�ʼ�ɣ���\n",ob);
                        operator = ob;
                        ob->save();
                        call_out("do_paimai",0,"automatic");
                } else
                {
                        CHANNEL_D->do_channel( ob, "sys", "�ڵ�����ϵͳ��" + me->name(1) + "�ɹ�����������ģʽ���ֹ���");
                        ob->set("operator",me->query("id"));		//��������Ϊ�ֹ�����
                        msg += HIR "��ѡ����ͨ���ֹ���ʽ�����������̣����ڿ��Կ�ʼ�ˡ�\n" NOR;
                        msg += HIR "����ָ�" + HIW + "paimai <�ڵ�ID>" + HIR + "��\n" NOR;
                        msg += HIR "������ʹ�ã�" + HIW + "autopaimai" + HIR + " ָ��������������ת���Զ����С�\n" NOR;
                        write(msg);
                        message_vision("$N�ֺǺǵĶԴ��˵�������������$n�������֣���\n",ob,me);
                        message_vision("$N�����еĴ���֣�صĽ���$n��Ȼ���˵�һ�ߡ�\n",ob,me);
                        operator = me;
                        last_time = time();		//��¼�ôβ���ʱ��
                        ob->set_heart_beat(1);		//�����ֹ������ػ�����
                        ob->save();
                }
        }
        return 1;
}

int do_paimai(string arg)
{
        object ob;
        string *heidian_list,now_heidian,msg,*heidian_key;
        mapping begin_heidian;
        int i;

        if (!query("paimai_start") || query("paimai_end"))
                return notify_fail("���ڲ�û���ڽ���������\n");

        if (!arg)
                return notify_fail("ָ���ʽ��paimai <�ڵ�ID>");

        if (query("now_paimai"))
                return notify_fail("�������ڽ���" + query("now_paimai") + "�ڵ�������������ż���\n");

        ob = this_object();
        heidian_list = query("heidian_list");
        begin_heidian = query("begin_heidian");

        if (ob != operator)		//���Զ���
        {
                if (this_player() != operator)
                        return notify_fail("�Բ�����������������" + operator->name(1) + "���ֽ����С�\n");

                if (sizeof(heidian_list) < 1)		//�Ѿ�ȫ�����������
                {
                        set("can_finish",1);
                        save();
                        return notify_fail("���кڵ궼�Ѿ����������ˣ�������Ӧ�ý���(finish)�����ˡ�\n");
                }

                if (!begin_heidian[arg])		//�ύ�Ĳ�������������ʾ���д������ڵ��б�
                {
                        msg = HIR "�Բ��������ύ��" + HIW + arg + HIR + "�ڵ겢�����ڡ�\n" NOR;
                        msg += HIC "�������ڵ��б� \n" NOR;
                        msg += HIC "--------------------------------------\n" NOR;
                        heidian_key = keys(begin_heidian);
                        for (i = 0;i < sizeof(heidian_key);i++)
                                msg += sprintf(HIY "%s" HIW "\t%s\n" NOR,heidian_key[i],begin_heidian[heidian_key[i]]);
                        msg += HIC "--------------------------------------\n" NOR;
                        msg += HIC "�ܹ�" + HIW + chinese_number(sizeof(heidian_key)) + HIC + "�Һڵꡣ\n";
                        msg += HIR "����ָ�" + HIW + "paimai <�ڵ�ID>" + HIR + "��\n" NOR;
                        msg += HIR "������ʹ�ã�" + HIW + "autopaimai" + HIR + " ָ��������������ת���Զ����С�\n" NOR;
                        write(msg);
                        return 1;
                }
                now_heidian = arg;		//��ǰ�����ڵ�
        } else	//�Զ�����
        {
                if (sizeof(heidian_list) < 1)	//ȫ���ڵ궼�Ѿ��������
                {
                        ob->set("can_finish",1);
                        ob->save();
                        call_out("finish_paimai",0);		//���ý�����������
                        return 1;
                }
                now_heidian = heidian_list[random(sizeof(heidian_list))];		//��ǰ�����ڵ�
        }

        heidian_list -= ({ now_heidian });	//�Ӵ��ĺڵ���ɾ����ǰ�����ڵ�
        ob->set("wait_jupai",1);
        ob->set("heidian_list",heidian_list);
        ob->delete("begin_heidian/" + now_heidian);
        ob->set("now_heidian",now_heidian);
        ob->set("now_price",(int)begin_heidian[now_heidian]);
        ob->save();

        CHANNEL_D->do_channel( ob, "sys", "���ڿ�ʼ����" + now_heidian + "�ڵꡣ");
        message_vision("$N��������������������" + HIW + now_heidian + NOR + "�ڵ꣡�׼ۣ�" + HIW + begin_heidian[now_heidian] + NOR + "���ƽ��һ�Σ���\n",operator);
        message_vision("$N�����˵���������������߾���(" + HIW + "jupai" + NOR + "������\n",operator);

        if (ob == operator)			//�Զ�����
                call_out("begin_paimai",DISTANCE);
        else
                last_time = time();	//��¼�ôβ�����ʱ��

        return 1;
}

int begin_paimai()
{
        string now_heidian;
        int now_price,m;
        object operator,ob;

        ob = this_object();

        m = ob->query("wait_jupai");

        if (!m) return 1;		//�Ѿ����˿�ʼ����

        now_heidian = query("now_heidian");
        now_price = query("now_price");

        m +=1;
        ob->set("wait_jupai",m);

        if (operator != ob)		//�ֹ����������ִ�е���ʦ�Ƿ��ڣ���������ˣ�����������ת�Զ�
                operator = check_operator();
                
        message_vision("$N����������������" + HIW + now_heidian + NOR + "�ڵ꣡�׼ۣ�" + HIW + now_price + NOR + "���ƽ��" + chinese_number(m) + "�Σ���\n",operator);
        message_vision("$N�����˵���������������߾���(" + HIW + "jupai" + NOR + "������\n",operator);

        if (operator == ob)		//�Զ�����
        {
                if (!(m==3))
                        call_out("begin_paimai",DISTANCE);
                else
                        call_out("stop_paimai",DISTANCE);
        } else			//�ֹ����� 
                last_time = time();	//��¼���һ�β�����ʱ��     
}

int stop_paimai()
{
        string now_heidian,temp_owner,*owner,*heidian_list,msg,*heidian_key;
        mapping begin_heidian,end_heidian;
        object ob,the_owner;
        int i,now_price;

        ob = this_object();
        owner = query("owner");
        temp_owner = query("temp_owner");
        heidian_list = query("heidian_list");
        begin_heidian = query("begin_heidian");
        end_heidian = query("end_heidian");
        now_heidian = query("now_heidian");
        now_price = query("now_price");

        if (!mapp(end_heidian) || sizeof(end_heidian) < 1) end_heidian = ([]);

        if (operator != ob)		//�ֹ����������ִ�е���ʦ�Ƿ��ڣ���������ˣ�����������ת�Զ�
                operator = check_operator();

        if (query("wait_jupai"))
        {
                message_vision("$N�������е�Сľ�������һ�ã�ֻ���á���������һ�����졣\n",operator);
                message_vision("$N������������" + HIW + now_heidian + NOR + "�ڵ������Ȩ���������ˡ�\n",operator);
                end_heidian[now_heidian] = 0;
                ob->delete("wait_jupai");
                ob->delete("now_heidian");
                ob->set("end_heidian",end_heidian);
                ob->save();
                if (operator == ob)	//�Զ�����
                {
                        if (sizeof(heidian_list) < 1)		//���кڵ���������
                        {
                                set("can_finish",1);
                                save();
                                call_out("finish_paimai",0);
                                return 1;
                        }
                        call_out("do_paimai",1,"automatic");
                }
                else
                {
                        if (sizeof(heidian_list) < 1)		//���кڵ���������
                        {
                                set("can_finish",1);
                                save();
                                tell_object(operator,"���кڵ궼�Ѿ����������ˣ�������Ӧ�ý���(finish)�����ˡ�\n");
                                return 1;
                        }
                        msg += HIC "�������ڵ��б� \n" NOR;
                        msg += HIC "--------------------------------------\n" NOR;
                        heidian_key = keys(begin_heidian);
                        for (i = 0;i < sizeof(heidian_key);i++)
                                msg += sprintf(HIY "%s" HIW "\t%s\n" NOR,heidian_key[i],begin_heidian[heidian_key[i]]);
                        msg += HIC "--------------------------------------\n" NOR;
                        msg += HIC "�ܹ�" + HIW + chinese_number(sizeof(heidian_key)) + HIC + "�Һڵꡣ\n";
                        msg += HIR "����ָ�" + HIW + "paimai <�ڵ�ID>" + HIR + "��\n" NOR;
                        msg += HIR "������ʹ�ã�" + HIW + "autopaimai" + HIR + " ָ��������������ת���Զ����С�\n" NOR;
                        tell_object(operator,msg);
                        last_time = time();	//��¼�ôβ���ʱ��
                }
                return 1;
        }
        else            
        {
                //���ȼ�鵱ǰ��Ͷ�ڵ������Ƿ����ߣ������Ƿ���Ͷ���ϻ�Ǯׯȡ���˴��
                //�������������쳣����úڵ����¹�����ĺڵ����飬����ȡ������ҵ������ʸ�

                the_owner = find_player(temp_owner);
                if (!objectp(the_owner) || the_owner->query("balance") < now_price * 10000)
                {
                        do_unwelcome(temp_owner + " 1");		//ȡ������ҵ������ʸ�
                        begin_heidian[now_heidian] = 2000;
                        ob->set("begin_heidian",begin_heidian);

                        message_vision("$N����������������" + temp_owner + "�����쳣��ȡ������ҵ������ʸ�" + HIW + now_heidian + NOR + "�ڵ����¹���������б���\n",operator);
                        CHANNEL_D->do_channel( ob, "sys", "����" + temp_owner + "�����쳣��ȡ������ҵ������ʸ�" + now_heidian + "�ڵ����¹���������б�");
                } else
                {
                        the_owner->add("balance",-now_price);
                        the_owner->save();
                        owner += ({ temp_owner });
                        ob->set("owner",owner);
                        end_heidian[now_heidian] = now_price;
                        ob->set("end_heidian",end_heidian);
                        HEIDIAN_D->setowner(operator,now_heidian,temp_owner);
                        message_vision("$N�������е�Сľ�������һ�ã�ֻ���á���������һ�����졣\n",operator);
                        message_vision("$N�������������ɽ���" + temp_owner + "�����" + HIW + now_heidian + NOR + "�ڵ������Ȩ�����ճ��ۣ�" + HIW + now_price + NOR + "���ƽ𣡡�\n",operator);
                        CHANNEL_D->do_channel( ob, "sys", "�ɽ���" + temp_owner + "�����" + now_heidian + "�ڵ������Ȩ�����ճ��ۣ�" + now_price + "���ƽ�");
                        tell_object(the_owner,HIR "��ϲ��ϲ������" + now_price + "���ƽ�ļ۸����ջ��" + now_heidian + "�ڵ������Ȩ��\n" NOR);
                }        
                ob->delete("on_jupai");
                ob->delete("now_heidian");
                ob->delete("now_price");
                ob->delete("temp_owner");
                ob->save();

                if (operator == ob)		//�Զ�����
                {
                        if (sizeof(heidian_list) < 1)		//���кڵ���������
                        {
                                set("can_finish",1);
                                save();    
                                call_out("finish_paimai",0);
                                return 1;
                        }
                        call_out("do_paimai",1,"automatic");
                } else
                        if (sizeof(heidian_list) < 1)		//���кڵ���������
                        {
                                set("can_finish",1);
                                save();
                                tell_object(operator,"���кڵ궼�Ѿ����������ˣ�������Ӧ�ý���(finish)�����ˡ�\n");
                                return 1;
                        }
                        msg += HIC "�������ڵ��б� \n" NOR;
                        msg += HIC "--------------------------------------\n" NOR;
                        heidian_key = keys(begin_heidian);
                        for (i = 0;i < sizeof(heidian_key);i++)
                                msg += sprintf(HIY "%s" HIW "\t%s\n" NOR,heidian_key[i],begin_heidian[heidian_key[i]]);
                        msg += HIC "--------------------------------------\n" NOR;
                        msg += HIC "�ܹ�" + HIW + chinese_number(sizeof(heidian_key)) + HIC + "�Һڵꡣ\n" NOR;
                        msg += HIR "����ָ�" + HIW + "paimai <�ڵ�ID>" + HIR + "��\n" NOR;
                        msg += HIR "������ʹ�ã�" + HIW + "autopaimai" + HIR + " ָ��������������ת���Զ����С�\n" NOR;
                        tell_object(operator,msg);
                        last_time = time();	//��¼�ôβ���ʱ��
                }
                return 1;
        }
}

int do_jupai(object buyer,string arg)
{
        object ob;
        string now_heidian,temp_owner;
        int money,now_price;

        ob = this_object();
        if(!query("paimai_start"))
                return notify_fail("����������û�п�ʼ���㼱��ɶ������ص㣬С��ȡ����ȡ�������ʸ�\n");

        if (operator != ob)		//�ֹ����������ִ�е���ʦ�Ƿ��ڣ���������ˣ�����������ת�Զ�
                operator = check_operator();

        if(!query("now_heidian"))
                return notify_fail(operator->name(1) + "��û������Ҫ�����ļҺڵ꣬�㼱��ɶ��\n");

        if(member(buyer->query("id"),query("owner")))
                return notify_fail("���Ѿ����ĵ�������Ҫ�ĺڵ꣬�Ĳ�Ҫ��ô�ڣ�������Ļ����������˰ɣ�\n");

        if(member(buyer->query("id"),query("unwelcom")))
                return notify_fail("���Ѿ���ȡ���������ʸ�����ʵʵһ�ߴ��Űɡ�\n");

        if(buyer->query("id") == query("temp_owner"))
                return notify_fail("��ǰ�ļ۸�������������Ͷ�İ���ͷ���ˣ�\n");

        remove_call_out("begin_paimai");
        remove_call_out("go_jupai");
        now_heidian = query("now_heidian");
        now_price = query("now_price");
        temp_owner = buyer->query("id");

        if (!arg)
                money = 100;
        else
                if (!(sscanf(arg,"%d",money) == 1) || money < 100)
                        return notify_fail("ָ���ʽ��jupai [num]��num�����ӵĻƽ�������100�������ָ��num�����ʾ�Ӽ�100���ƽ�\n");

        if (buyer->query("balance") < (money + now_price)*10000)
                return notify_fail("���ʻ����Ǯ������" + (money+now_price) + "���ƽ��ˡ�\n");

        now_price += money;
        
        ob->set("temp_owner",temp_owner);
        ob->set("on_jupai",1);
        ob->set("now_price",now_price);
        ob->delete("wait_jupai");
        ob->save();

        tell_object(buyer,"����˾����е����ӣ�ʾ��Ӽ�" + chinese_number(money) + "���ƽ�\n");
        message_vision("$N������������" + temp_owner + "����" + HIW + now_price + NOR + "���ƽ���" + HIW + now_heidian + NOR + "�ڵ��һ�Σ���\n",operator);

        if (operator == ob)		//�Զ�����
                call_out("go_jupai",DISTANCE);
        else
                last_time = time();	//��¼��ǰ����ʱ��

        return 1;
}

int go_jupai()
{
        object ob;
        int m,now_price;
        string now_heidian,temp_owner;
        
        ob = this_object();
        m = query("on_jupai");
        now_heidian = query("now_heidian");
        now_price = query("now_price");
        temp_owner = query("temp_owner");

        m+=1;
        ob->set("on_jupai",m);
        ob->save();

        if (operator != ob)		//�ֹ����������ִ�е���ʦ�Ƿ��ڣ���������ˣ�����������ת�Զ�
                operator = check_operator();

        message_vision("$N������������" + temp_owner + "����" + HIW + now_price + NOR + "���ƽ���" + HIW + now_heidian + NOR + "�ڵ��" + chinese_number(m) + "�Σ���\n",operator);

        if (operator == ob)		//�Զ�����
        {
                if (!(m==3))
                        call_out("go_jupai",DISTANCE);
                else
                        call_out("stop_paimai",DISTANCE);
        } else			//�ֹ����� 
                last_time = time();	//��¼���һ�β�����ʱ��     

        return 1;
}

int do_qiao(object me)
{
        object ob;
        int m;
        ob = this_object;

        if (!query("paimai_start"))
                return notify_fail("�����������̻�û��������������ʹ��startָ���������������̡�\n");

        if (operator != ob)		//�ֹ����������ִ�е���ʦ�Ƿ��ڣ���������ˣ�����������ת�Զ�
                operator = check_operator();

        if (operator != me)
                return notify_fail("����������������" + operator->name(1) + "�����У�������Ҫ��ʲô���ȱ�ˮ����֧�̣���Ϣ��Ϣ��\n");

        //�Ѿ��������ĺڵ꣬�ȴ�������
        if (m = query("wait_jupai"))
        {
                if (!(m == 3))
                        call_out("begin_paimai",0);
                else
                        call_out("stop_paimai",0);
        } else if (m = query("on_jupai"))
        {
                if (!(m == 3))
                        call_out("go_jupai",0);
                else
                        call_out("stop_paimai",0);
        } else return notify_fail("�������������������ĸ��ڵꡣ\n");
        return 1;
}

int do_paimailist(object me)
{
        int i;
        string msg,now_paimai,*heidian_list,*heidian_key;
        mapping begin_heidian,end_heidian;

        msg = "";
        now_paimai = query("now_paimai");
        begin_heidian = query("begin_heidian");
        end_heidian = query("end_heidian");

        if (query("paimai_start"))
                msg += HIC "������������֮�С�\n" NOR;
        else
                msg += HIC "���ڲ�û���������ڵꡣ\n" NOR;

        msg += HIC "--------------------------------------\n" NOR;

        if (now_paimai)
        {
                msg += sprintf(HIY"��ǰ�����ڵ꣺"HIW"%s\t"NOR HIR"%s\n"NOR, now_heidian, now_price);
                msg += HIC "--------------------------------------\n" NOR;
        }

        is (mapp(begin_heidian) && sizeof(begin_heidian) > 0)
        {
                msg += HIY "�������ڵ��б� \n" NOR;
                heidian_key = keys(begin_heidian);
                for (i = 0;i < sizeof(heidian_key);i++)
                        msg += sprintf(HIW "%s" HIR "\t%s\n" NOR,heidian_key[i],begin_heidian[heidian_key[i]]);
                msg += HIC "--------------------------------------\n" NOR;
        }

        is (mapp(end_heidian) && sizeof(end_heidian) > 0)
        {
                msg += HIY "�ѱ������ڵ��б� \n" NOR;
                heidian_key = keys(end_heidian);
                for (i = 0;i < sizeof(heidian_key);i++)
                        msg += sprintf(HIW "%s" HIR "\t%s\n" NOR,heidian_key[i],end_heidian[heidian_key[i]]);
                msg += HIC "--------------------------------------\n" NOR;
        }

        tell_object(me,msg);
        return 1;
}

int do_unwelcome(string arg)
{
        int i,m;
        string *unwelcome;
        unwelcome = query("unwelcome");
        if (!unwelcome || sizeof(unwelcome) < 1) unwelcome = ({});
        if (!arg)
        {
                if (sizeof(unwelcome) < 1)
                        return notify_fail("����û����Ҹ�ȡ�������ʸ�\n");

                msg = HIC "��ȡ�������ʸ������б�\n"NOR;
                msg += HIC"------------------------------------\n"NOR;
                for (i = 0;i < sizeof(unwelcome);i++)
                        msg += HIY unwelcome[i] + "\n"NOR;
                msg += HIC"------------------------------------\n"NOR;
                msg += HIC"�ܹ�" + sizeof(unwelcome) + "λ��Ҹ�ȡ�������ʸ�\n"NOR;
                tell_object(me,msg);
                return 1;
        }

        if (sscanf(arg,"%s %d",arg,m) != 2) m = 1;

        if (m)
        {
                if (member(arg,unwelcome) == -1)
                {
                        unwelcome += ({ arg });
                        set("unwelcome",unwelcome);
                }
        }
        else
        {
                if (member(arg,unwelcome) != -1)
                {
                        unwelcome -= ({ arg });
                        set("unwelcome",unwelcome);
                }
        }
        save();
        return 1;
}

int finish_paimai(object me)
{
        if (!query("paimai_start"))
                return notify_fail("�������̲�û���������Զ�����ɶŶ��\n");

        if (!query("can_finish"))
                return notify_fail("�����������ڽ���֮�У��޷���ֹ��\n");

        if (operator != me)
                return notify_fail("������" + operator->name(1) + "���ֺڵ����������ͱ�����ˡ�\n");

        ob->delete("can_finish");
        ob->delete("heidian_list");
        ob->delete("begin_heidian");
        ob->delete("heidian_start");
        ob->set("heidian_end",1);
        ob->delete("wait_jupai");
        ob->delete("on_jupai");
        ob->delete("now_heidian");
        ob->delete("now_price");
        ob->delete("temp_owner");
        ob->delete("owner");
        ob->save();
        message_vision("$N���������������κڵ�����Բ����������\n",operator);

        if (operator == ob)
        {
                HEIDIAN_D->open_all(operator);
                message_vision("$N���������������ĺڵ������Ѿ�ȫ�����ţ���\n",operator);
        } else tell_object(operator,"�����ڿ�����openshopָ��źڵꡣ\n");
        return 1;
}

//������--���ڼ�������������̵���ʦ�Ƿ�״̬����
//���״̬����������תΪ�Զ�����ģʽ�����ҹر�������
void heart_beat()
{
        int m;
        object obj;
        string the_operator;

        if (!query("paimai_start") || operator == this_object())
        {
                set_heart_beat(0);
                return;
        }

        the_operator = query("operator");
        if (!the_operator)
        {
                set_heart_beat(0);
                return;
        }

        if (!(obj = find_player(the_operator)) || !living(obj) || environment(obj) != environment() || time() - last_time > 10)
        {
                operator = this_object();
                set_heart_beat(0);
                command("say ����" + the_operator + "�е�������Ҫæ�������������������������֣�");
                CHANNEL_D->do_channel( ob, "sys", "����" + the_operator + "״̬�쳣��������������ת���Զ�ģʽ��");
                set("operator","fujia tianxia");
                save();
                if (m = query("wait_jupai"))
                {
                        if (!(m == 3))
                               call_out("begin_paimai",DISTANCE);
                        else
                               call_out("stop_paimai",DISTANCE);
                } else if (m = query("on_jupai"))
                {
                        if (!(m == 3))
                                call_out("go_jupai",DISTANCE);
                        else
                                call_out("stop_paimai",DISTANCE);
                } else call_out("do_paimai",0,"automatic");
        }
        return;
}

object check_operator()
{
        object obj;
        string the_operator;

        the_operator = query("operator");

        if (!(obj = find_player(the_operator)) || !living(obj) || environment(obj) != environment() || time() - last_time > 10)
        {
                set("operator","fujia tianxia");
                save();
                return this_object();
        }
        return obj;
}

int do_autopaimai(object me)
{
        if (!query("paimai_start"))
                return notify_fail("�������̲�û���������Զ�����ɶŶ��\n");

        if (operator != me)
                return notify_fail("���������ֲ��������˼������֣�������ô���İɡ�\n");

        operator = this_object();
        set_heart_beat(0);
        command("say ����" + me->name(1) + "�е�������Ҫæ�������������������������֣�");
        CHANNEL_D->do_channel( ob, "sys", me->query("id") + "����������ת���Զ�ģʽ��");
        set("operator","fujia tianxia");
        save();
        if (m = query("wait_jupai"))
        {
                if (!(m == 3))
                        call_out("begin_paimai",DISTANCE);
                else
                        call_out("stop_paimai",DISTANCE);
        } else if (m = query("on_jupai"))
        {
                if (!(m == 3))
                        call_out("go_jupai",DISTANCE);
                else
                        call_out("stop_paimai",DISTANCE);
        } else call_out("do_paimai",0,"automatic");
        return 1;
}