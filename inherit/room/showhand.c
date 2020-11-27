// suoha.c �����ֻ֧������, Written by LLM
#define DIAN(x)     (x-1)/4
#define HUA(x)     x%4
#include <ansi.h>
inherit ROOM;

object *player=({});//���
int *cards = ({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
20,21,22,23,24,25,26,27,28});//���е���
int yazhu=0;//����Ѻע�ı��
int chouma=0;//�����Ѿ�Ѻ�ϵĳ���
int yazhu_chouma=0;//����Ѻ��������ĳ�����
int wait_time=0;//�ȴ�������Ǻ�
int quansuo=0;//ȫ��
mapping *suoha_cards=({
([
"anpai":0,
"mingpai":({}),
]),//ׯ�ҵ���
([
"anpai":0,
"mingpai":({}),
]),//�Լҵ���
});
string *all_card=({"��","��","��","��","��","��","��" });
string *all_sort=({HIB"����",HIR"��Ƭ",HIC"�ݻ�",HIR"����",});
string *all_pai=({"ɢ��","һ��","����","����","˳��","ͬ��","�ɻ�","ը��","ͬ��˳"});

void suoha_init();
void deal_an_card();
void deal_ming_card();
int check_player(object);
int do_yazhu(string);
int do_gen();
object gen_ob(object);
void ob_win(object);
void game_over();
int do_buya();
int do_leave();
int do_quansuo();
string look_pai();
string type_paiju(object);
int check_chouma();
string query_obs();

string type_card(int x)//���ű���
{
    return sprintf("%s%s%s"NOR,all_sort[HUA(x)],HIW,all_card[DIAN(x)]);
}

string type_cards(mapping pai)//���ű���
{
    switch(pai["lv"])
    {
    case 2:
       return sprintf("%s��Լ�%sС�ԣ�������",type_card(pai["ddui"]),type_card(pai["xdui"]));
    case 3:
    case 6:
    case 7:
        return sprintf(HIW"%s%s%s",all_card[DIAN(pai["max"])],NOR,all_pai[pai["lv"]]);
    default:
    return sprintf("%s%s",type_card(pai["max"]),all_pai[pai["lv"]]);
    }
}

mapping juesuan(int *ob_allcard)//������Ƶ�����
{
    mapping pai;
    int i,x,flag,*L;
    
    flag=0;
    x=sizeof(ob_allcard);
    L=sort_array(ob_allcard,1);//����
    switch(x)
    {
    case 1:
        pai=([
            "lv": 0,
            "max" : L[0],
            ]);
        break;
    case 2:
        if(DIAN(L[0])==DIAN(L[1]))//������ͬ�Ƕ���
            pai=([
                "lv": 1,
                "max" : L[1],//ȡ���ӵĴ���
            ]);
        else
            pai=([
                "lv": 0,
                "max" : L[1],
            ]);
        break;
    case 3:
        if(DIAN(L[0])==DIAN(L[2]))//��һ�����������ͬ����ֻ
            pai=([
                "lv": 3,
                "max" : L[2],//���ȡһ��
            ]);
        else if(DIAN(L[0])==DIAN(L[1]))//ֻ��һ��������ͬ ����
            pai=([
                "lv": 1,
                "max" : L[1],//ȡ����
            ]);
        else if(DIAN(L[1])==DIAN(L[2]))//ֻ�ж���������ͬ ����
            pai=([
                "lv": 1,
                "max" : L[2],//ȡ����
            ]);
        else
            pai=([
                "lv": 0,
                "max" : L[2],//ȡ�����
            ]);
        break;
    case 4:
        if(DIAN(L[0])+1==DIAN(L[1])&&DIAN(L[1])+1==DIAN(L[2])&&DIAN(L[2])+1==DIAN(L[3]))
            flag=1;
        if(HUA(L[0])==HUA(L[1])&&HUA(L[2])==HUA(L[3])&&HUA(L[1])==HUA(L[2]))//ͬ�����ٿ��Ƿ�˳��
        {
            if(!flag)//ͬ��
                pai=([
                "lv": 5,
                "max" : L[3],
                ]);
            else//ͬ��˳
                pai=([
                "lv": 8,
                "max" : L[3],
                ]);
        }
        else if(flag)//˳��
            pai=([
            "lv": 4,
            "max" : L[3],
            ]);
        else if(DIAN(L[0])==DIAN(L[3]))//һ�ĵ�����ͬ��ը��
            pai=([
                "lv": 7,
                "max" : L[0],//���ȡһ��
            ]);
        else if(DIAN(L[0])==DIAN(L[2])||DIAN(L[1])==DIAN(L[3]))//һ������ĵ�����ͬ������
            pai=([
                "lv": 3,
                "max" : L[2],//���ȡһ�м���
            ]);
        else if(DIAN(L[0])==DIAN(L[1])&&DIAN(L[2])==DIAN(L[3]))//һ�������ĵ�����ͬ������
            pai=([
                "lv": 2,
                "xdui":L[1],
                "ddui":L[3],
                "max":L[3],//ȡ������
            ]);
        else
        {
            if(DIAN(L[0])==DIAN(L[1])) flag=1;
            else if(DIAN(L[1])==DIAN(L[2])) flag=2;
            else if(DIAN(L[2])==DIAN(L[3])) flag=3;
        if(flag)
            pai=([
                "lv": 1,
                "max" : L[flag],//ȡ���ӵĴ���
            ]);
        else
            pai=([
                "lv": 0,
                "max" : L[3],//ȡ������
            ]);
        }
        break;
    case 5:    
        if(DIAN(L[0])+1==DIAN(L[1])&&DIAN(L[1])+1==DIAN(L[2])&&DIAN(L[2])+1==DIAN(L[3])&&DIAN(L[3])+1==DIAN(L[4]))
            flag=1;
        if(HUA(L[0])==HUA(L[1])&&HUA(L[1])==HUA(L[2])&&HUA(L[2])==HUA(L[3])
            &&HUA(L[3])==HUA(L[4]))//��ͬ����ֻ���Ƿ�˳����������
        {
            if(!flag)//ͬ��
                pai=([
                "lv": 5,
                "max" : L[4],
                ]);
            else//ͬ��˳
                pai=([
                "lv": 8,
                "max" : L[4],
                ]);
        }
        else if(flag)//˳��
            pai=([
            "lv": 4,
            "max" : L[4],
            ]);
        else if(DIAN(L[0])==DIAN(L[3])||DIAN(L[1])==DIAN(L[4]))//1,4��2,5��ͬ����Ϊը����ȡ������
        {
            pai=([
            "lv": 7,
            "max" : L[4],//��ɫ�޹ؽ�Ҫ��ը��ֻҪ�жϵ���
            ]);
        }
        else if(DIAN(L[0])==DIAN(L[2])||DIAN(L[2])==DIAN(L[4])||DIAN(L[1])==DIAN(L[3]))//����һ��
        {
            if((DIAN(L[0])==DIAN(L[2])&&DIAN(L[3])==DIAN(L[4]))
                ||(DIAN(L[2])==DIAN(L[4])&&DIAN(L[0])==DIAN(L[1])) )//��ʣ�����Ƕ���
            {
                pai=([
                "lv": 6,
                "max" : L[2],//ȡ�м����ţ���ɫ�޹ؽ�Ҫ
                ]);
            }
            else
                pai=([
                "lv":3,
                "max" : L[2],//ȡ�м����ţ���ɫ�޹ؽ�Ҫ
                ]);
        }
        else
        {
        flag=0;
        if(DIAN(L[0])==DIAN(L[1])&&DIAN(L[2])==DIAN(L[3])) flag=3;
        if(DIAN(L[0])==DIAN(L[1])&&DIAN(L[3])==DIAN(L[4])) flag=4;
        if(DIAN(L[1])==DIAN(L[2])&&DIAN(L[3])==DIAN(L[4])) flag=4;
        if(flag)//С���ӿ϶���1������ӿ϶���3
        {
            pai=([
                "lv": 2,
                "xdui":L[1],
                "ddui":L[3],
                "max" : L[flag],//ȡ����ӵĴ���
            ]);
        }
        else
        {
        for(i=0;i<4;i++)
            if(DIAN(L[i])==DIAN(L[i+1])) flag=(i+1);
        if(flag)
            pai=([
            "lv": 1,
            "max" : L[flag],//ȡ���ӵĴ���
            ]);
        else
            pai=([
            "lv": 0,
            "max" : L[4],//ȡ������
            ]);
        }
        }
        break;
    }
    return pai;
}
    
int bi_daxiao(mapping card1,mapping card2)//�ȴ�С,card1�����0��card2�����1
{
    if(card1["lv"]==card2["lv"])//ͬ�����
    {
        if(card1["lv"]== 2)//������
        {
            if(DIAN(card1["ddui"])>DIAN(card2["ddui"])) 
                return 0;
            else if(DIAN(card1["ddui"])==DIAN(card2["ddui"]))
            {
                if(DIAN(card1["xdui"])>DIAN(card2["xdui"])
                    ||(DIAN(card1["xdui"])==DIAN(card2["xdui"])
                    &&card1["max"]>card2["max"]))
                    return 0;
                else return 1;
            }
            else return 1;
        }
        else if(card1["max"]>card2["max"]) return 0;
        else return 1;
    }
    else if(card1["lv"]>card2["lv"]) return 0;
    else return 1;
}

int do_sit()
{
        object me;
        int i;
        me = this_player();

    if (me->query_temp("suoha/being"))
                return notify_fail("���Ѿ��������ˣ�\n");
    if(me->query_temp("duchang_chouma")<200)
        return notify_fail("��ĳ���̫���ˣ�\n");
    i=sizeof(player);
        if (i<2)//���п�λ
        {
        me->set_temp("suoha/being",1);
                player+=({me});
                me->add_temp("duchang_chouma",-5);//Ѻ����
                yazhu_chouma+=5;//����
        i=sizeof(player);
        message_vision("$N�ó�5������Ѻ��ȥ����������λ��\n",me);
        if (i == 2)//��2���Զ���ʼ
                {
               tell_room(this_object(), HIM"    �ã����Կ�ʼ�����ˣ�\n"NOR);
                        suoha_init();
                }
                return 1;
        }
        else
                return notify_fail("�����Ѿ������ˣ�\n");
}

void suoha_init()
{
    chouma+=yazhu_chouma;
    yazhu_chouma=0;//����
    deal_an_card();
}

void deal_an_card()//������
{
        int i, j;

    i=random(sizeof(cards));//���ȡһ��
    suoha_cards[0]["anpai"]=cards[i];//�������а���
    message_vision("\n$N�õ���һ�Ű��ƣ�����һ�ۺ�Ѹ�ٵظ������ϣ�\n",player[0]);
    tell_object(player[0],"���Ű����ǣ�"+type_card(cards[i])+"��\n");
    cards-=({cards[i]});//���������Ʊ�����

    i=random(sizeof(cards));//��ʣ���������������ȡһ��
    suoha_cards[1]["anpai"]=cards[i];//�������а���
    message_vision("\n$N�õ���һ�Ű��ƣ�����һ�ۺ�Ѹ�ٵظ������ϣ�\n",player[1]);
    tell_object(player[1],"���Ű����ǣ�"+type_card(cards[i])+"��\n");
    cards-=({cards[i]});//���������Ʊ�����
    tell_room(this_object(), HIM"    ���ڿ�ʼ��ÿ���˷������ˣ�\n"NOR);
        remove_call_out("deal_ming_card");//һ��󷢵ڶ���
        call_out("deal_ming_card",1);//һ��󷢵ڶ���
}

void deal_ming_card()//������
{
    int i,j;
    string arg;
    mapping card1,card2;

    i=random(sizeof(cards));//���ȡһ��
    suoha_cards[0]["mingpai"]+=({cards[i]});//�������е�����
    message_vision("\n$N�õ���һ�ţ�" +type_card(cards[i])+"��\n",player[0]);
    cards-=({cards[i]});//���������Ʊ�����
    i=random(sizeof(cards));//ʣ�µ��������ȡһ��
    suoha_cards[1]["mingpai"]+=({cards[i]});//�������е�һ������
    message_vision("\n$N�õ���һ�ţ�" +type_card(cards[i])+"��\n",player[1]);
    cards-=({cards[i]});//���������Ʊ�����

    card1=juesuan(suoha_cards[0]["mingpai"]);//���������
    card2=juesuan(suoha_cards[1]["mingpai"]);//���������
    j=bi_daxiao(card1,card2);//�ȳ�����
    tell_object(player[0],type_paiju(player[0]));
    tell_object(player[1],type_paiju(player[1]));
    if(j) arg=type_cards(card2);
    else arg=type_cards(card1);
    message_vision(HIY"\n����$N��"+arg+HIY"˵����\n"NOR,player[j]);
    player[j]->set_temp("suoha/shuohua",1);
    tell_object(player[j],"\n����Ѻ��ya <������>,��Ѻ(buya)�����䣡\n");
        yazhu=1;//����Ѻע��
        call_out("check_player",60,player[j]);//һ���Ӻ���
    return;
}

int check_player(object me)
{
    object ob;
    
    if(!wait_time)
    {
        wait_time=1;
        call_out("check_player",10,me);//���ʮ��;
        tell_object(me,"�㻹��ʮ����ʱ�䣬��ʱ�ͱ�ʾ���䣡\n");
        return 1;
    }
    yazhu=0;
    wait_time=0;
    message_vision("$N��ʱ�����ˣ���������ƣ�\n");
    ob=gen_ob(me);
    call_out("juesheng",0,ob,1);//��ʤ
    return 1;
}

int do_yazhu(string arg)
{
    int i;
    string str;
    object me,ob;
    me=this_player();
    if(!yazhu) return notify_fail("���ڲ�����ע��ʱ��\n");
    if(!me->query_temp("suoha/shuohua"))//�Ƿ�Ϊ˵���ķ���
        return notify_fail("���ڲ�����˵����\n");
     if(!arg||sscanf(arg,"%d",i)!=1||(i!=5&&i!=10&&i!=20))
        return notify_fail("��ҪѺ���ٳ��룿��ѡ5��,10��,20�����롣\n");
    remove_call_out("check_player");//�����ʱ����
    me->add_temp("duchang_chouma",-i);
    yazhu_chouma=i;
    message_vision("$N����һ��������ȥһЩ����˵������Ѻ "+i+" �����Ҹ��𣿡�\n",me);
    ob=gen_ob(me);
    tell_object(ob,"��Ҫ��(gen)�Ļ�����������"+i+"�����룬��Ѻ(buya)�������䣡\n");
    me->delete_temp("suoha/shuohua");
    ob->set_temp("suoha/genhua",1);
    call_out("check_player",60,ob);
    return 1;
}

int do_gen()
{
    int i;
    object me,ob;
    me=this_player();
    if(!yazhu) return notify_fail("���ڲ��Ǹ�ע��ʱ��\n");
    if(!me->query_temp("suoha/genhua"))
        return notify_fail("���ڲ�����˵����\n");
    remove_call_out("check_player");//�����ʱ����
    i=yazhu_chouma;//ǰ����Ѻ�µĳ�����
    me->add_temp("duchang_chouma",-i);
    chouma+=(i*2);//�����˵ĳ��붼�ӽ�ȥ
    yazhu_chouma=0;//����
    message_vision("$N΢΢һЦ��Ҳ����һЩ������ȥ��˵�����Ҹ� ����\n",me);
    me->delete_temp("suoha/genhua");
    if(sizeof(suoha_cards[0]["mingpai"])==4)//�Ʒ�����
    {
        yazhu=0;
        message_vision("\n���ѷ��꣬��������ƣ�\n",me);
        call_out("juesheng",1,me,0);//��ʤ
    }
    else//�����ٷ���
    {
        remove_call_out("deal_ming_card");
            call_out("deal_ming_card",1);
        }
    return 1;
}
//���Ƶ���
object gen_ob(object ob)
{
   if(sizeof(player)<2) return 0;
    if(player[0]==ob)
        return player[1];
    else
        return player[0];
}

int juesheng(object ob,int flag)//flagΪ��,�򲻹ܽ������obʤ
{
    mapping card1,card2;
    int i,*pai1,*pai2;
    
    pai1=suoha_cards[0]["mingpai"];
    pai1+=({suoha_cards[0]["anpai"]});
    card1=juesuan(pai1);
    
    pai2=suoha_cards[1]["mingpai"];
    pai2+=({suoha_cards[1]["anpai"]});
    card2=juesuan(pai2);
    
    i=bi_daxiao(card1,card2);

    message_vision("\n$N�����ǡ�"+type_cards(card1)+"��\n"
    "\n$n�����ǡ�"+type_cards(card2)+"��\n",player[0],player[1]);
    if(!flag)
        ob=player[i];
    else
    {
        if(ob!=player[i])
            message_vision("$N�ûڵ����ĺ����ף�����֪���Ҿ�......����\n",player[i]);
        else
            message_vision("$N����ص��ͷ����Ҳ��������֪֮������\n",player[i]);
    }
    message_vision("\n��ϲ$Nʤ�������ϳ���ȫ�գ�\n",ob);
    ob_win(ob);
    return 1;
}

void ob_win(object ob)
{
    ob->add_temp("duchang_chouma",chouma);
    message_vision("\n��һ�֣�$Nһ��Ӯ��"+chouma+"�����룡\n",ob);
    game_over();
}

void game_over()
{
    if(sizeof(player))
    {
        player[0]->delete_temp("suoha");
        message_vision("$Nվ��������\n",player[0]);
    }
    if(sizeof(player)>1)
    {
        player[1]->delete_temp("suoha");
        message_vision("$Nվ��������\n",player[1]);
    }
    player=({});
    chouma=0;
    yazhu_chouma=0;
    suoha_cards=({
    ([
        "anpai":0,
        "mingpai":({}),
    ]),//ׯ�ҵ���
    ([
        "anpai":0,
        "mingpai":({}),
    ]),//�Լҵ���
    });
    wait_time=0;
    quansuo=0;
    cards =({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28});//���е���
//--------end---------
}

int do_buya()
{
    int i;
    object me,ob;
    me=this_player();
    if(!yazhu) return notify_fail("���ڲ��Ǹ�ע��ʱ��\n");
    if(!me->query_temp("suoha/shuohua")&&!me->query_temp("suoha/genhua"))//�Ƿ�Ϊ˵���ķ���
        return notify_fail("���ڲ�����˵����\n");
    remove_call_out("check_player");//�����ʱ����

    chouma+=yazhu_chouma;//�ӽ�ǰ����Ѻ�µĳ�����
    yazhu_chouma=0;//����
    message_vision("$N������ü��ͻȻһЦ��˵�����Ҳ����� ����\n",me);
    yazhu=0;
    message_vision("$N�������ƣ���������ƣ�\n",me);
    ob=gen_ob(me);
    call_out("juesheng",1,ob,1);//��ʤ
    return 1;
}

int do_leave()
{
    object me,ob;
    me = this_player();

    if (!me->query_temp("suoha/being"))
                return notify_fail("������û��������������߾�ֱ�ӳ����š�\n");
    ob=gen_ob(me);
    if(ob)//�Ѿ���������
    {
        if(!yazhu)//��δ������
            return notify_fail("�����ڲ����뿪!\n");
        yazhu=0;
        remove_call_out("check_player");//�����ʱ����
        message_vision("$N���������ˣ�\n",me);
        chouma+=yazhu_chouma;//�ӽ�ǰ����Ѻ�µĳ�����
        call_out("juesheng",0,ob,1);//��ʤ
    }
    else//ֻ��һ���ˣ����ǻ�û����
    {
        me->add_temp("duchang_chouma",yazhu_chouma);//���ո�Ѻ�ķ���
        yazhu=0;
        remove_call_out("check_player");//�����ʱ����
        message_vision("$N���������ˣ�\n",me);
        chouma+=yazhu_chouma;//�ӽ�ǰ����Ѻ�µĳ�����
        call_out("game_over",0);//����
    }
    return 1;
}

int do_quansuo()//ȫ��
{
    int i;
    string str;
    object me,ob;
    me=this_player();
    if(!yazhu) return notify_fail("���ڲ�����ע��ʱ��\n");
    if(sizeof(suoha_cards[0]["mingpai"])!=4)//�Ʒ�����,���һ��
        return notify_fail("���ڲ������һ�ţ�����showhand��\n");
    if(quansuo)
        return notify_fail("�Է��Ѿ�showhand�ˣ���ֻҪ������(gen)���ǲ���(buya)��\n");
    if(!me->query_temp("suoha/shuohua")&&!me->query_temp("suoha/genhua"))
        return notify_fail("���ڲ�����˵����\n");
    remove_call_out("check_player");//�����ʱ����
    quansuo=1;
    if(me->query_temp("suoha/shuohua"))//˵����
    {
    i=(200-chouma/2);//�����200,̨������һ��
    me->add_temp("duchang_chouma",-i);
        me->delete_temp("suoha/shuohua");
    yazhu_chouma=i;
    }
    else if(me->query_temp("suoha/genhua"))//������
    {
    i=yazhu_chouma;//�ȸ���ǰ�����Ѻ��ע
    me->add_temp("duchang_chouma",-i);
    chouma+=i*2;
    i=(200-chouma/2);
    me->add_temp("duchang_chouma",-i);
        me->delete_temp("suoha/genhua");
    yazhu_chouma=i;
    }
    message_vision("$N����ǰ�ĳ��롰������һ��ȫ������ȥ������ȫ���ˣ��Ҹ��𣿡�\n",me);
    ob=gen_ob(me);
    tell_object(ob,"��Ҫ��(gen)�Ļ�����������"+i+"�����룬��Ѻ(buya)�������䣡\n");
    ob->set_temp("suoha/genhua",1);
    call_out("check_player",60,ob);
    return 1;
}

string look_pai()
{
    switch(sizeof(player))
    {
    case 0:
        return "���ϵ��ƾֻ�û�п�ʼ�أ�\n";
    case 1:
        return "����"+player[0]->name()+"���������ϵȺ���˵ļ��룡\n";
    case 2:
        return type_paiju(this_player());
    }
}

string type_paiju(object me)
{
    string str,name1,name2,an1,an2;
    int *pai1,*pai2,i,j,k;
    
    pai1=suoha_cards[0]["mingpai"];
    pai2=suoha_cards[1]["mingpai"];
    i=sizeof(pai1);
    j=sizeof(pai2);
    an1=an2="������";//Ĭ��
    if(player[0]==me)
    {
        an1= type_card(suoha_cards[0]["anpai"]);
        name1="��";
    }
    else
        name1=player[0]->name();
    if(player[1]==me)
    {
        an2= type_card(suoha_cards[1]["anpai"]);
        name2="��";
    }
    else
        name2=player[1]->name();
    str=sprintf("����%s���ƣ�%s%s\n"
"��������������������������������������������������\n"
"��������������������������������������������������\n"
"��%s��",name1,(player[0]->query_temp("suoha/shuohua")?HIW"˵��"NOR:""),
    (player[0]->query_temp("suoha/genhua")?HIW"����"NOR:""),an1);
    for(k=0;k<4;k++)
    {
        if(k<i)
            str+=sprintf("��%s��",type_card(pai1[k]));
        else
            str+="����������";
    }
    str+=sprintf("\n"
"��������������������������������������������������\n"
"��������������������������������������������������\n\n"
"����%s���ƣ�%s%s\n"
"��������������������������������������������������\n"
"��������������������������������������������������\n"
"��%s��",name2,(player[1]->query_temp("suoha/shuohua")?HIW"˵��"NOR:""),
    (player[1]->query_temp("suoha/genhua")?HIW"����"NOR:""),an2);
    for(k=0;k<4;k++)
    {
        if(k<j)
            str+=sprintf("��%s��",type_card(pai2[k]));
        else
            str+="����������";
    }
    str+="\n"
"��������������������������������������������������\n"
"��������������������������������������������������\n\n";
    str+=sprintf("�������ϵĳ�������%dֻ��Ҫ�����ĳ�����Ϊ%dֻ��\n\n",chouma,yazhu_chouma);
    return str;
}

int valid_leave(object me, string dir)
{
    if(me->query_temp("suoha"))
        return notify_fail("�����ڴ����أ�Ҫ�������뿪(leave)������\n");
    return ::valid_leave(me, dir);
}

int check_chouma()
{
    int i;
    object me=this_player();
    if(!i=me->query_temp("duchang_chouma"))
        return notify_fail("������û���κγ��룡\n");
    write("Ŀǰ������һ����"+chinese_number(i)+"ֻ���룡\n");
    return 1;
}
