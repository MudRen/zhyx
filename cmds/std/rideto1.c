

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
           return notify_fail("你还没有座骑！\n");
        }        
      
       if ( wizardp(me) && (! objectp(riding) || ! present(riding, me) ))
           me->set_temp("is_riding", me); 
	    
		 if (me->query("doing") == "scheme")
                        return notify_fail("你现在正在执行计划，不能骑马走人。\n");

       if( !arg )
                return notify_fail("指令格式：rideto <地名> 详情可以 <help rideto>。\n");

	if (me->is_busy())
		return notify_fail("你上一个动作还没有完成！\n");
	if (me->query("doing"))
		return notify_fail("你没空前去！\n");
	
	if (me->over_encumbranced())
                return notify_fail("你的负荷过重，动弹不得。\n");
        if (me->is_fighting())
                return notify_fail("你还在战斗中！没空前去。\n");
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
                return notify_fail(WHT"这个地方没法骑座骑过去。\n"NOR);
       
                 env = environment(me);
       if (file_name(env)[0..5] == "/d/pk/" || env->query("no_ride") 
           || file_name(env)[0..11] == "/d/zhuanshi/" ) 
                return notify_fail("这里不能骑马走人！\n");  
      target = arg;
      me->this_player();
     if (target == "gc" || target == "yangzhou")
        {
              me->move("d/city/guangchang");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向扬州广场方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else 
     if (target == "sz" || target == "suzhou")
        {
              me->move("d/suzhou/zhongxin");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向苏州城中心方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "bj" || target == "beijing")
        {
              me->move("d/beijing/tiananmen");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向北京天安门方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "bt" || target == "baituo")
        {
              me->move("d/baituo/shijie");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向白驼山方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg, env, ({ me, env }));

         return 1;
        } else      if (target == "ca" || target == "changan")
        {
              me->move("d/changan/nan-chengmen");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向长安方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "cd" || target == "chengdu")
        {
              me->move("d/city3/southgate");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向成都方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "dl" || target == "daili")
        {
              me->move("d/dali/center");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向大理广场方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "em" || target == "emei")
        {
              me->move("d/emei/fhs");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向峨嵋方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "fs" || target == "foshan")
        {
              me->move("d/foshan/southgate");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向佛山方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "fz" || target == "fuzhou")
        {
              me->move("d/fuzhou/dongmen");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向福州广场方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "hz" || target == "hangzhou")
        {
              me->move("d/hangzhou/road13");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向杭州广场方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "hmy" || target == "heimuya")
        {
              me->move("d/heimuya/guang");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向黑木崖方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "hs" || target == "henshan")
        {
              me->move("d/henshan/nantian");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向衡山方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "hgs" || target == "hengshan")
        {
              me->move("d/hengshan/jinlongxia");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向恒山方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "has" || target == "huashan")
        {
              me->move("d/huashan/path1");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向华山方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "jz" || target == "jingzhou")
        {
              me->move("d/jingzhou/guangchang");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向荆州广场方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "kf" || target == "kaifeng")
        {
              me->move("d/kaifeng/nanying");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向开封方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "kl" || target == "kunlun")
        {
              me->move("d/kunlun/guangchang");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向昆仑方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else      if (target == "km" || target == "kunming")
        {
              me->move("d/kunming/jinrilou");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向昆明方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    
          if (target == "lz" || target == "lanzhou")
        {
              me->move("d/lanzhou/guangchang");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向兰州广场方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "xx" || target == "xingxiu")
        {
              me->move("d/xingxiu/tianroad2");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向星宿方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "lx" || target == "lingxiao")
        {
              me->move("d/lingxiao/shanya");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向灵宵城方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "lgz" || target == "lingzhou")
        {
              me->move("d/lingzhou/center");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向灵州方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "ly" || target == "luoyang")
        {
              me->move("d/luoyang/center");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向洛阳广场方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "mj" || target == "mingjiao")
        {
              me->move("d/mingjiao/tomen2");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向明教方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "qz" || target == "quanzhen")
        {
              me->move("d/quanzhen/damen");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向全真教方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else    if (target == "sl" || target == "shaolin")
        {
              me->move("d/shaolin/smdian");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向少林寺方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else   
         if (target == "ss" || target == "songshan")
        {
              me->move("d/songshan/taishique");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向嵩山方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else  if (target == "ts" || target == "taishan")
        {
              me->move("d/taishan/taishanjiao");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向泰山方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else  if (target == "wd" || target == "wudang")
        {
              me->move("d/wudang/xuanyuegate");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向武当山方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else  if (target == "xy" || target == "xiangyang")
        {
              me->move("d/xiangyang/jiekou1");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向襄阳方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else  if (target == "xs" || target == "xueshan")
        {
              me->move("d/xueshan/shanmen");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向雪山方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        } else  if (target == "zz" || target == "zhongzhou")
        {
              me->move("d/zhongzhou/shizhongxin");
       riding = me->query_temp("is_riding");
       msg = me->name() + "骑着" + riding->name() + "向中州广场方向疾驰而去。\n";     
       msg = replace_string(msg, "$N", me->name() + HIM);
       message("vision", msg + NOR, env, ({ me, env }));

         return 1;
        }
 
          return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : rideto <地名>
 
这个指令你可以用你的坐骑去到你想去的地方。

yangzhou(gc) : 扬  州  beijing(bj) : 北  京  chengdu(cd)  : 成  都
changan(ca)  : 长  安  hangzhou(hz): 杭  州  suzhou(sz)   : 苏  州
xiangyang(xy): 襄  阳  fuzhou(fz)  : 福  州  foshan(fs)   : 佛  山
lingzhou(lgz): 灵  州  jingzhou(jz): 荆  州  zhongzhou(zz): 中  州        
songshan(ss) : 嵩  山  dali(dl)    : 大  理  kunming(km)  : 昆  明
wudang(wd)   : 武  当  taishan(ts) : 泰  山  quanzhen(qz) : 全  真
emei(em)     : 峨  眉  lanzhou(lz) : 兰  州  changan(ca)  : 长  安
baituo(bt)   : 白驮山  heimuya(hmy): 黑木崖  mingjiao(mj) : 光明顶
xingxiu(xx)  : 星宿海  henshan(hs) : 衡  山  hengshan(hgs): 恒  山
huashan(has) : 华  山  xueshan(xs) : 雪  山  kaifeng(kf)  : 开  封
kunlun(kl)   : 昆仑山  lingxiao(lx): 灵宵城  shaolin(sl)  : 少  林 

HELP );
        return 1;
}
