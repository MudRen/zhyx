// linzhennan.c ������
// modified by Jay 4/7/96
#include <ansi.h>
string do_quest();
inherit NPC;
int ask_fuwei();
int ask_yuantu();
int ask_pixie();
int ask_tong();
void create()
{
        set_name("������", ({ "lin zhennan", "lin", "zhennan" }));
        set("gender", "����");
        set("age", 45);
        set("long", "�����ǡ������ھ֡�������ͷ���������ϡ�\n");
        set("combat_exp", 30000);
        set("shen_type", 1);
        set("max_neili", 500);
        set("neili", 500);
        set("jiali", 10);
        set_skill("force", 40);
        set("per",19);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set("inquiry", ([
                "������լ" : "������˵���������Ҵ�ǰ�ڸ���ʱס�ļ�Ժ���Ѿ��ư��ˡ�\n",
                "�����ھ�" : (: ask_fuwei :),
                "Զͼ��" : (: ask_yuantu :),
                "��Զͼ" : "�����ϴ�ŭ��С������ôû��ò��ֱ���������䣡\n",
                "��а����" : (: ask_pixie:),
                "ͭǮ" : (: ask_tong:),
                "ͭ��" : (: ask_tong:),
        "����":(:do_quest:),
        "��": (:do_quest:),
        ]) );
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 15);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
    carry_object("/clone/misc/long_cloth")->wear();
}
int ask_fuwei()
{
 say("��������ҫ��˵�������ּ��������ڣ�һ����������Զͼ�����괳�µ���������\n"
     "�����������ּҼҴ������ն����㺬��������н��յľ��棬��Ϊ����������\n"
     "һָ�Ĵ��ھ֡��������ᵽ�������ھ֡����֣�˭��Ҫ�����Ĵָ��˵һ������\n"
     "�ø����������磡��������������\n");
 this_player()->set_temp("marks/��1", 1);
 return 1;
}
int ask_yuantu()
{
  if ((int)this_player()->query_temp("marks/��1")) {
 say("�����Ͽ�һ���̶���˵����Զͼ�����ҵ��游�������ھ�����һ�ִ���ġ�����\n"
     "�游����ʮ��·��а���������ھ֣������Ǵ��ڵ��޵��֡���ʱ�׵���Ӣ�ۼ�\n"
     "��̫�����磬Ҳ��ȥ�����������յģ�����������������ʦ������������֮ʱ\n"
     "��������а���������˼��С�\n");
 this_player()->set_temp("marks/��2", 1);
 return 1;
  }
  else {
 say("������˵����Զͼ�����ҵ��游��\n");
 return 1;
  }
}
int ask_pixie()
{
  int p1, p2, p3, p4;
  if ((int)this_player()->query("passwd")) {
 say("�����ϲ��õ�˵�����Ҳ��Ƕ������������ҵĽ����������档\n");
  }
  else if ((int)this_player()->query_temp("marks/��2")) {
 say("������һ����˵��������ô֪���ģ��ޣ��Ҹղ�˵¶���ˡ��ˣ����µĹ�������\n"
     "��֪��ϸ����ʵ���������档��\n");
 write("�����϶�һ�٣����Ŷ������˵������ȥ��ǰ�������Ҹ�����");
 p1=random(4)+1;
 p2=random(4)+1;
 p3=random(4)+1;
 p4=random(4)+1;
 this_player()->set("passwd",p1*1000+p2*100+p3*10+p4);
 write(CHINESE_D->chinese_number(p1)+"ǧ"+CHINESE_D->chinese_number(p2)+
       "��"+CHINESE_D->chinese_number(p3)+"ʮ"+CHINESE_D->chinese_number(p4));
 write("��\nͭǮ����һֱδ�����а��ء�\n");
  }
  else {
   message("vision",
   HIY "�����ϲ�Ȼ��ŭ���ȵ�����Ҳ���������ּҵı�а���ף����Ҹ���ƴ�ˣ�\n"
   NOR, environment(), this_object() );
   kill_ob(this_player());
  }
  this_player()->delete_temp("marks/��1");
  this_player()->delete_temp("marks/��2");
  return 1;
}
int ask_tong()
{
  int p, p1, p2, p3, p4;
  if (!(p=(int)this_player()->query("passwd"))) {
 say("������һ����Ц�����ӣ�˵����ô�쵽��һ���˵���ҪǮ��\n");
  }
  else {
 write("�����ϵ���˵������ȥ��ǰ�������Ҹ�����");
 p1=(int)p/1000;
 p2=(int)(p-p1*1000)/100;
 p3=(int)(p-p1*1000-p2*100)/10;
 p4=(int)(p-p1*1000-p2*100-p3*10);
 write(CHINESE_D->chinese_number(p1)+"ǧ"+CHINESE_D->chinese_number(p2)+
       "��"+CHINESE_D->chinese_number(p3)+"ʮ"+CHINESE_D->chinese_number(p4));
 write("��\nͭǮ����һֱδ�����а��ء�\n");
  }
  return 1;
}
string chinese_time(int t)
{
    int d, h, m, s;
    string time;
    s = t % 60;     t /= 60;
    m = t % 60;     t /= 60;
    h = t % 24;     t /= 24;
    d = t;
    if(d) time = chinese_number(d) + "��";
    else time = "";
    if(h) time += chinese_number(h) + "Сʱ";
    if(m) time += chinese_number(m) + "��";
    time += chinese_number(s) + "��";
    return time;
}
string do_quest()
{
        mapping target=([
        "tang nan":         "�����ϰ� ���",
        "yue buqun":        "��ɽ���������š����ӽ�������Ⱥ",
        "post officer":     "�䳤�ſ�",
        "ping yizhi":       "ҩ���ϰ� ƽһָ",
        "wu liuqi":          "��ػ��˳����������ؤ��������",
       // "tai jian":         "̫��",
   //     "shi wei":          "����",
  //      "chen mingjing":    "����֪�� ������",
   //     "mo yixin":         "ҩ���ϰ� Īһ��",
        "xu zhu":           "���չ������ˡ����ɡ�����",
        "xuanku dashi":     "�����ɵ���ʮ�������ӡ��޺��������������ʦ",
        "xuannan dashi":    "�����ɵ���ʮ�������ӡ����������������Ѵ�ʦ",
        "ning zhongze":     "��ɽ�ɵ�ʮ�������� ������",
   //     "ma juwei":         "ؤ���ߴ����� ���Ϊ",
    //    "jian zhanglao":    "ؤ��Ŵ����ϡ�ִ�����ϡ�����",
    //    "hong qigong":      "ؤ���ʮ�ߴ���������ָ��ؤ�����߹�",
        "yu lianzhou":      "�䵱�ɵڶ������ӡ��䵱������������",
        "song yuanqiao":    "�䵱�ɵڶ������ӡ��䵱��������Զ��",
        "li lishi":         "������",
     //   "yu hongxing":      "ؤ��˴����� �����",
      //  "zhaixing zi":      "�����ɵڶ������ӡ������ɴ�ʦ�֡�ժ����",
     //   "zhang sanfeng":    "�䵱�ɿ�ɽ��ʦ���������ˡ�������",
        "jinlun fawang":    "���� ���ַ���",
        "chen jin nan":     "�����ſ�ɽ��ʦ��Ӣ���޵С��½���",
        "guan anji":        "����ϰ塸�ط��ӡ��ذ���",
        "lazhang huofo":    "��� ���»��",
        "you xun":          "���������֡���Ѷ",
        "li mochou":        "���������ӡ���Ī��",
        //"lao ban":          "��Ц���䡹����ϰ�",
   //     "yuan chanshi":     "�Ѿ������� Բ����ʦ",
        "jia laoliu":       "�����ϰ� ������",
  //      "chen mapo":        "���Ŷ�����ʼ�ˡ�������ʩ��������",
   //     "xuan zhen":        "�����ŵڶ������� �������",
   //     "huang yaoshi":     "�һ�����ɽ��ʦ����а����ҩʦ",
   //     "hong antong":      "�����̽����������ɸ����鰲ͨ",        
        "ouyang feng":      "�϶��������ŷ����",
        "ding chunqiu":     "�����ɿ�ɽ��ʦ�������Ϲ֡�������",
   //     "li defa":          "ҩ���ϰ� ��÷�",
        "ben yin":          "���������� ����",
        "jiang baisheng":   "����ʤ",
//      "zhang wuji":       "���̽��� ���޼�",
//      "wei yixiao":       "������������ ΤһЦ",
        "ouye zi":          "�����ɿ�ɽ��ʦ�����Ľ�����ŷұ��",
        ]);
/*���³����м����ۺ����������������Ҫ��.�������£� 
    ���ڴ�������һ���Ϳ������� ���Σ������Ը߾Ϳ�������������,
    ��������������quest,�����վ�ڹ㳡�����ʽ�,�������ǻ�������
    �ӣ� ���ش�������Ϸquest��ƽ��,Ѱ� ɱ�ˣ����ŵ�quest������
    ��Ϸ��Ƶ���Ҫquest,ּ����Ҿ�����ߵĹ�����,���������Ϥmud��ͼ
    ��MUD NPC����,������ȴ���٣�Ϊʲô�����������������һ���ѶȰ���
    .��Ϸ�������ǲ����л�����.���ּ���score�����������İ취δ�غã�
    ���ǿ��У�ϣ����ҹ�ͬ��ı�����ҳ����õ���Ʒ���.(�ڷ��εĳ�����
    ����score���������Ҳ�ɻ���̫�����ͬʱ�����������)*/
       int ran, t, time;
        string *str;
        object ob, who, home;
          ob=this_object();
        if(!home = find_object(ob->query("startroom")) )
                home = load_object(ob->query("startroom"));
        if (environment(ob)!=home){
                return("��������æ���أ����һ�ȥ��˵�ɣ�");
        }
        who = this_player();
        
//expdif �����жϴ����ڿ�ʼ��ԭ��exp�����ӵ�exp��score�Ĺ�ϵ,��������ұ�Թ.        
/*if (!who->query("expcheck")){
        bexp = who->query("combat_exp");
        who->set("bas_exp",bexp);
        who->set("expcheck",1);
}*/
    
    if (who->query("family/family_name")=="������"){
    return who->name()+"����ô��ʦҲ�������˻�ˮ��\n";
}

    if (who->query("combat_exp")>10000000)
     return("��λ"+RANK_D->query_respect(who)+"�Ĵ�����������˭�˲�֪���ĸ����������ٱξ֣�������ң�\n");
/*sc = who->query("score");
    expdif = (int)who->query("combat_exp")-(int)who->query("bas_exp");
    if (expdif >50000&&sc < 100)
       return(RED"������ڽ����Ϻ���ûʲô���֣��Ҷ��㲻����ģ�\n"NOR);
    else if (expdif >100000&&sc < 500)
       return(RED"������ڽ����Ϻ���ûʲô���֣��Ҷ��㲻����ģ�\n"NOR);
    else if (expdif >300000&&sc < 1000)
       return(RED"������ڽ����Ϻ���ûʲô���֣��Ҷ��㲻����ģ�\n"NOR);
    else if (expdif >400000&&sc < 3000)
       return(RED"������ڽ����Ϻ���ûʲô���֣��Ҷ��㲻����ģ�\n"NOR);
    else if (expdif >600000&&sc < 7000)
       return(RED"������ڽ����Ϻ���ûʲô���֣��Ҷ��㲻����ģ�\n"NOR);
    else if (expdif >1000000&&sc < 10000)
       return(RED"������ڽ����Ϻ���ûʲô���֣��Ҷ��㲻����ģ�\n"NOR);
    else if (expdif >1500000&&sc < 16000)
       return(RED"������ڽ����Ϻ���ûʲô���֣��Ҷ��㲻����ģ�\n"NOR);
    else if (expdif >2000000&&sc <25000)
       return(RED"������ڽ����Ϻ���ûʲô���֣��Ҷ��㲻����ģ�\n"NOR);
     else if (expdif>6000000&&sc< 30000)
       return(RED"������ڽ����Ϻ���ûʲô���֣��Ҷ��㲻����ģ�\n"NOR);
*/
        t = time()-who->query("biao_start");
        time = who->query("biao_time");
        if( t <= time )
                return  RANK_D->query_respect(who)+ "�ƺ�������������ɣ�\n";
        if( t > time && t < (time + 300) ) {
                if( ob = present("biao yin", who) ) destruct(ob);
                who->set("biao_failed",1);
        }
        if( t >= (time + 300) )
                who->delete("biao_failed");
        if(who->query("biao_failed") ) {
                command("hehe " + who->query("id"));
                return this_player()->name() + "����ӡ�÷��ڣ�����ʧ�����ҿ����ǲ����������ˡ�\n";
        }
        t = ( 30 + random(10) ) * 10;
        str=keys(target);
        ran = random(sizeof(str));
        ob = new("/clone/misc/biaoyin");
        ob->set("target", str[ran]);
        who->set("biao_start", time());
        who->set("biao_time", t);
        ob->move(who);
       who->set("env/brief",1);
        return ("���������ã�����һ�������͵�" + target[str[ran]] + "�����\n"+"�㻹��" + chinese_time(t)+ "��ʱ�䡣��춯��ɣ�\n");
        
}
