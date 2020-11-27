

#include <ansi.h>

inherit F_CLEAN_UP;
int main(object me, string arg)
{
	 string target;
        string msg;
        object env;
        object riding;    
    
       
       riding = me->query_temp("is_riding");

        if ( (! objectp(riding) || ! present(riding, me) ) && ! wizardp(me))
       {
           me->delete_temp("is_riding");
           return notify_fail("�㻹û�����\n");
        }        
      
       if ( wizardp(me) && (! objectp(riding) || ! present(riding, me) ))
           me->set_temp("is_riding", me); 
	    
		 if (me->query("doing") == "scheme")
                        return notify_fail("����������ִ�мƻ��������������ˡ�\n");

       if( !arg )
                return notify_fail("ָ���ʽ��rideto <����> ������� <help rideto>��\n");

	if (me->is_busy())
		return notify_fail("����һ��������û����ɣ�\n");
	if (me->query("doing"))
		return notify_fail("��û��ǰȥ��\n");
	
	if (me->over_encumbranced())
                return notify_fail("��ĸ��ɹ��أ��������á�\n");
        if (me->is_fighting())
                return notify_fail("�㻹��ս���У�û��ǰȥ��\n");
      if (  arg != "gc"     && arg != "yangzhou" &&
            arg != "sz"      && arg != "suzhou" &&
            arg != "bj"      && arg != "beijing" &&
            arg != "cd"      && arg != "chengdu" &&
            arg != "ca"      && arg != "changan" &&
            arg != "hz"      && arg != "hangzhou" &&
            arg != "xy"      && arg != "xiangyang" &&
            arg != "fz"      && arg != "fuzhou" &&
            arg != "fs"      && arg != "foshan" &&
            arg != "lgz"      && arg != "lingzhou" &&
            arg != "jz"      && arg != "jingzhou" &&
            arg != "sz"      && arg != "suzhou" &&
            arg != "qz"      && arg != "quanzhen" &&
            arg != "dl"      && arg != "dali" &&
            arg != "km"      && arg != "kunming" &&
            arg != "wd"      && arg != "wudang" &&
            arg != "ts"      && arg != "taishan" &&
            arg != "em"      && arg != "emei" &&
            arg != "lz"      && arg != "lanzhou" &&
            arg != "bt"      && arg != "baituo" &&
            arg != "hmy"      && arg != "heimuya" &&
            arg != "mj"      && arg != "mingjiao" &&
            arg != "xx"      && arg != "xingxiu" &&
            arg != "hs"      && arg != "henshan" &&
            arg != "hgs"      && arg != "hengshan" &&
            arg != "has"      && arg != "huashan" &&
            arg != "xs"      && arg != "xueshan" &&
            arg != "kl"      && arg != "kunlun" &&
            arg != "kf"      && arg != "kaifeng" &&
            arg != "lx"      && arg != "lingxiao" &&
            arg != "sl"      && arg != "shaolin" &&
            arg != "ly"      && arg != "luoyang" &&
            arg != "ss"      && arg != "songshan" &&
	    arg != "zz" && arg != "zhongzhou")
                return notify_fail(WHT"����ط�û���������ȥ��\n"NOR);
       
                 env = environment(me);
       if (file_name(env)[0..5] == "/d/pk/" || env->query("no_ride") 
           || file_name(env)[0..11] == "/d/zhuanshi/" ) 
                return notify_fail("���ﲻ���������ˣ�\n");  
      target = arg;
      me->this_player();
     if (target == "gc" || target == "yangzhou")
        {
              me->move("d/city/guangchang");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�����ݹ㳡���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else 
     if (target == "sz" || target == "suzhou")
        {
              me->move("d/suzhou/zhongxin");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�����ݳ����ķ��򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "bj" || target == "beijing")
        {
              me->move("d/beijing/tiananmen");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�򱱾��찲�ŷ��򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "bt" || target == "baituo")
        {
              me->move("d/baituo/shijie");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�����ɽ���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg, env, ({ me, env }));

         return 1;
        } else      if (target == "ca" || target == "changan")
        {
              me->move("d/changan/nan-chengmen");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�򳤰����򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "cd" || target == "chengdu")
        {
              me->move("d/city3/southgate");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "��ɶ����򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "dl" || target == "daili")
        {
              me->move("d/dali/center");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�����㳡���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "em" || target == "emei")
        {
              me->move("d/emei/fhs");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "����ҷ��򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "fs" || target == "foshan")
        {
              me->move("d/foshan/southgate");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "���ɽ���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "fz" || target == "fuzhou")
        {
              me->move("d/fuzhou/dongmen");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "���ݹ㳡���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "hz" || target == "hangzhou")
        {
              me->move("d/hangzhou/road13");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "���ݹ㳡���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "hmy" || target == "heimuya")
        {
              me->move("d/heimuya/guang");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "���ľ�·��򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "hs" || target == "henshan")
        {
              me->move("d/henshan/nantian");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "���ɽ���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "hgs" || target == "hengshan")
        {
              me->move("d/hengshan/jinlongxia");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "���ɽ���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "has" || target == "huashan")
        {
              me->move("d/huashan/path1");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "��ɽ���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "jz" || target == "jingzhou")
        {
              me->move("d/jingzhou/guangchang");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "���ݹ㳡���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "kf" || target == "kaifeng")
        {
              me->move("d/kaifeng/nanying");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�򿪷ⷽ�򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "kl" || target == "kunlun")
        {
              me->move("d/kunlun/guangchang");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�����ط��򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "km" || target == "kunming")
        {
              me->move("d/kunming/jinrilou");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "���������򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    
          if (target == "lz" || target == "lanzhou")
        {
              me->move("d/lanzhou/guangchang");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�����ݹ㳡���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "xx" || target == "xingxiu")
        {
              me->move("d/xingxiu/tianroad2");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�����޷��򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "lx" || target == "lingxiao")
        {
              me->move("d/lingxiao/shanya");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�������Ƿ��򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "lgz" || target == "lingzhou")
        {
              me->move("d/lingzhou/center");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�����ݷ��򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "ly" || target == "luoyang")
        {
              me->move("d/luoyang/center");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�������㳡���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "mj" || target == "mingjiao")
        {
              me->move("d/mingjiao/tomen2");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�����̷��򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "qz" || target == "quanzhen")
        {
              me->move("d/quanzhen/damen");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "��ȫ��̷��򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "sl" || target == "shaolin")
        {
              me->move("d/shaolin/smdian");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�������·��򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else   
         if (target == "ss" || target == "songshan")
        {
              me->move("d/songshan/taishique");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "����ɽ���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else  if (target == "ts" || target == "taishan")
        {
              me->move("d/taishan/taishanjiao");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "��̩ɽ���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else  if (target == "wd" || target == "wudang")
        {
              me->move("d/wudang/xuanyuegate");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "���䵱ɽ���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else  if (target == "xy" || target == "xiangyang")
        {
              me->move("d/xiangyang/jiekou1");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "���������򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else  if (target == "xs" || target == "xueshan")
        {
              me->move("d/xueshan/shanmen");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "��ѩɽ���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else  if (target == "zz" || target == "zhongzhou")
        {
              me->move("d/zhongzhou/shizhongxin");
       riding = me->query_temp("is_riding");
       msg = me->name() + "����" + riding->name() + "�����ݹ㳡���򼲳۶�ȥ��\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        }
 
          return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : rideto <����>
 
���ָ����������������ȥ������ȥ�ĵط���

yangzhou(gc) : ��  ��  beijing(bj) : ��  ��  chengdu(cd)  : ��  ��
changan(ca)  : ��  ��  hangzhou(hz): ��  ��  suzhou(sz)   : ��  ��
xiangyang(xy): ��  ��  fuzhou(fz)  : ��  ��  foshan(fs)   : ��  ɽ
lingzhou(lgz): ��  ��  jingzhou(jz): ��  ��  zhongzhou(zz): ��  ��        
songshan(ss) : ��  ɽ  dali(dl)    : ��  ��  kunming(km)  : ��  ��
wudang(wd)   : ��  ��  taishan(ts) : ̩  ɽ  quanzhen(qz) : ȫ  ��
emei(em)     : ��  ü  lanzhou(lz) : ��  ��  changan(ca)  : ��  ��
baituo(bt)   : ����ɽ  heimuya(hmy): ��ľ��  mingjiao(mj) : ������
xingxiu(xx)  : ���޺�  henshan(hs) : ��  ɽ  hengshan(hgs): ��  ɽ
huashan(has) : ��  ɽ  xueshan(xs) : ѩ  ɽ  kaifeng(kf)  : ��  ��
kunlun(kl)   : ����ɽ  lingxiao(lx): ������  shaolin(sl)  : ��  �� 

HELP );
        return 1;
}
