#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;


void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob,env;
        string pla, here;
        
        ob = me->query_temp("is_riding");

        if ( (! objectp(ob) || ! present(ob, me) ) && ! wizardp(me))
       {
           me->delete_temp("is_riding");
           return notify_fail("�㻹û�����\n");
        }
        
        if (! arg)
                return notify_fail("��Ҫȥ���\n");
				
				 if (me->query("doing") == "scheme")
                        return notify_fail("����������ִ�мƻ��������������ˡ�\n");

      
        if (me->is_fighting())
                return notify_fail("���������ں��˼Ҷ��֣� ������������ѽ��\n");
       if (me->query_temp("quest_biao"))
                return notify_fail("�ú�����,������.\n");

           env = environment(me); 
      //     if (! stringp(here = env->query("outdoors"))) 
      //          return notify_fail("�ڷ����ڲ����������ˣ�\n");

       if (file_name(env)[0..5] == "/d/pk/" || env->query("no_ride") 
           || file_name(env)[0..11] == "/d/zhuanshi/" ) 
                return notify_fail("���ﲻ���������ˣ�\n");        

        if (me->is_busy())
                return notify_fail("����һ��������û����ɣ��ȵȵȰɡ�\n");

          else {
          message_vision(HIY
"$N�������ϣ����һ������ඡ����ɱ���ȥ������\n"NOR, me);
}
          if(arg=="gc") pla = "/d/city/guangchang";
     else if(arg=="xingxiu") pla = "/d/xingxiu/xxh1";
     else if(arg=="mingjiao") pla = "/d/mingjiao/shanmen";
     else if(arg=="emei") pla = "/d/emei/huayanding";
     else if(arg=="shaolin") pla = "/d/shaolin/shanmen";
     else if(arg=="lingjiu") pla = "/d/lingjiu/jian";
     else if(arg=="duanshi") pla = "/d/dali/wangfugate";
     else if(arg=="wudang") pla = "/d/wudang/jiejianyan";
     else if(arg=="huashan") pla = "/d/huashan/laojun";
     else if(arg=="quanzhen") pla = "/d/quanzhen/jiaobei";
     else if(arg=="xiaoyao") pla = "/d/xiaoyao/xiaodao4";
     else if(arg=="gumu") pla = "/d/gumu/mumen";
     else if(arg=="kunlun") pla = "/d/kunlun/shanmen";
     else if(arg=="xuedao") pla = "/d/xuedao/wangyougu";
     else if(arg=="tiezhang") pla = "/d/tiezhang/shanmen";
     else if(arg=="dalun") pla = "/d/xueshan/shanmen";
     else if(arg=="songshan") pla = "/d/songshan/dadian";
     else if(arg=="shenlong") pla = "/d/shenlong/damen";
     else if(arg=="xuanming") pla = "/d/xuanminggu/shanjiao";
     else if(arg=="kaifeng") pla = "/d/kaifeng/zhuque";
     else if(arg=="kunming") pla = "/d/kunming/jinrilou";
     else if(arg=="wudu") pla = "/d/wudu/damen";
     else if(arg=="henshan") pla = "/d/henshan/nantian";
     else if(arg=="xueshan") pla = "/d/lingxiao/shanya";
     else if(arg=="riyue") pla = "/d/heimuya/pingdingzhou";
     else if(arg=="murong") pla = "/d/yanziwu/bozhou";
     else if(arg=="ouyang") pla = "/d/baituo/damen";
     else if(arg=="jueqing") pla = "/d/jueqing/shanzhuang";
     else if(arg=="guanwai") pla = "/d/guanwai/jishi";
     else if(arg=="dali") pla = "/d/dali/center";
     else if(arg=="beijing") pla = "/d/beijing/tiananmen";
     else if(arg=="changan") pla = "/d/changan/bridge2";
     else if(arg=="chengdu") pla = "/d/city3/guangchang";
     else if(arg=="foshan") pla = "/d/foshan/street3";
     else if(arg=="fuzhou") pla = "/d/fuzhou/dongjiekou";
     else if(arg=="guiyun") pla = "/d/guiyun/damen";
     else if(arg=="hangzhou") pla = "/d/hangzhou/road9";
     else if(arg=="jingzhou") pla = "/d/jingzhou/guangchang";
     else if(arg=="lingzhou") pla = "/d/lingzhou/center";
     else if(arg=="luoyang") pla = "/d/luoyang/center";
     else if(arg=="quanzhou") pla = "/d/quanzhou/zhongxin";
     else if(arg=="suzhou") pla = "/d/suzhou/zhongxin";
     else if(arg=="zhongzhou") pla = "/d/zhongzhou/shizhongxin";
     else if(arg=="ruzhou") pla = "/d/shaolin/ruzhou";
     else if(arg=="xiangyang") pla = "/d/xiangyang/guangchang"; 
     else if(arg=="lanzhou") pla = "/d/lanzhou/guangchang"; 
     else if(arg=="lingxiao") pla = "/d/lingxiao/shanya";  
     else if(arg=="taohua") pla = "/d/taohua/damen";
     else if(arg=="baituo") pla = "/d/baituo/shijie";
     else if(arg=="shangjia") pla = "/d/shaolin/shang_men";
     else if(arg=="hujia") pla = "/d/guanwai/xiaoyuan";
     else if(arg=="honghua") pla = "/d/kaifeng/hh_damen";
     else if(arg=="zhenyuan") pla = "/d/beijing/gate";
     else if(arg=="meizhuang"
     && me->query("family/family_name") == "÷ׯ") pla = "/d/meizhuang/keting";
     else if(arg=="wugong") pla = "/d/quanzhen/zhongxin";             else {
               message_vision(HIR
"����û������ط�����ôȥѽ��\n"NOR, me);
}
       me->move(pla);
  /*   if (me->move(pla)) {
       message_vision(HIC"\n���ˣ�������ȵ�ͣ��������\n"NOR,me);
           
 }              */
     return 1;
}


int help(object me)
{
        write(@HELP
ָ���ʽ : rideto <�ص�>
���ָ������������ϻ��߳������浽��ĳ���ص�.
���Ե���ĵص��У�
��    ��<xingxiu>    ��    ��<mingjiao>    ��    ��<emei>       ��    ��<shaolin>   
��    ��<lingjiu>    ��    ��<duanshi>     ��    ��<wudang>     ��    ɽ<huashan>   
��    Ĺ<gumu>       ��    ��<kunlun>      Ѫ �� ��<xuedao>     ��    ��<tiezhang>  
��    ɽ<songshan>   ��    ��<shenlong>    �� ڤ ��<xuanming>   ��    ��<wudu>      
ѩ    ɽ<xueshan>    ��    ��<riyue>       ȫ    ��<quanzhen>   ��    ң<xiaoyao>
��    ��<dalun>      ��    ɽ<henshan>     Ľ������<murong>     ŷ������<ouyang>
�� �� ��<jueqing>    �� �� ׯ<guiyun>      ��    ��<guanwai>    �� �� ��<dali>
��    ��<beijing>    ��    ��<chengdu>     ��    ɽ<foshan>     ��    ��<fuzhou>
��    ��<hangzhou>   ��    ��<jingzhou>    ��    ��<lingzhou>   ��    ��<luoyang>
Ȫ    ��<quanzhou>   ��    ��<suzhou>      ��    ��<zhongzhou>  ���ݹ㳡<gc>
��    ��<xiangyang>  ��    ��<kaifeng>     ��    ��<kunming>    ��    ��<lanzhou>
��    ��<ruzhou>     ��    ��<wugong>      ��    ��<lingxiao>   ��     ��<taohua>
÷    ׯ<meizhuang>  (����÷ׯ����ʹ�ã�   ��    ��<shangjia>   ��     ��<hujia>
�� �� ��<honghua>    ��Զ�ھ�<zhenyuan>

 
HELP
    );
    return 1;
}


