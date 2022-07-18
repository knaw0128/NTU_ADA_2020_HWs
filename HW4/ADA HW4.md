# ADA HW4

和李長諺、石容居、鄭天盛討論

## Problem 5

### (1) 
取$K=max(|T-\Sigma_{i=1}^{n}|a_{i}||+1, |a_{i}|)$
接著把$S$中所有元素都加上$K$並在$S$中加入$n$個$K$形成$S^{'}$，然後把$T$加上$nK$
因此$S^{'}$中所有數都不會是負的，符合$JJBAP_{+}$的條件

* 當$JJBAP_{+}$為True時，代表可以從$S^{'}$中取出$k$個數字$a_{b_{1}}^{'}...a_{b_{k}}^{'}$
    使得$\Sigma^{k}_{i=1}a_{b_{i}}^{'}=T+nK$ ($b_{i}$為一數列)
    已知$K>\Sigma_{i=1}^{n}|a_{i}|-T,\ K>T-\Sigma_{i=1}^{n}|a_{i}|$
    * 假設$k=n-d\ (1\le d<n,d\in N)$，因為$a_{i}^{'}=a_{i}+K$所以可以得到
        $\Sigma^{m}_{i=1}a_{b_{i}}+(n-d)K=T+nK\ (0<m\le n-d)\ \to K=\frac{\Sigma^{m}_{i=1}a_{b_{i}}-T}{d}且K為正$
        取$d=1使得K$最大則$K=\Sigma^{m}_{i=1}a_{b_{i}}-T\le \Sigma_{i=1}^{n}|a_{i}|-T$
        又$K>\Sigma_{i=1}^{n}|a_{i}|-T$ 因此矛盾，所以$k$不小於$n$
    * 假設$k=n+d\ (d\ge 1,d\in N)$，因為$a_{i}^{'}=a_{i}+K$所以可以得到
        $\Sigma^{m}_{i=1}a_{b_{i}}+(n+d)K=T+nK\ (0<m\le n+d)\ \to K=\frac{T-\Sigma^{m}_{i=1}a_{b_{i}}}{d}且K為正$
        取$d=1使得K$最大則$K=\Sigma^{m}_{i=1}a_{b_{i}}-T\le \Sigma_{i=1}^{n}|a_{i}|-T$
        又$K>\Sigma_{i=1}^{n}|a_{i}|-T$ 因此矛盾，所以$k$不大於$n$
        
    
    因此$k$一定會等於$n$，因此可以對兩邊同減去$nK$，$\Sigma^{k}_{i=1}(a_{b_{i}}^{'}-K)=T$
    而$a_{i}^{'}$減去$K$會是0或是$a_{i}$中的某個元素，因此$\Sigma^{k}_{i=1}(a_{b_{i}}^{'}-K)$會是一些$a_{i}$的元素和0的和
    因此可以得到某些$a_{i}$的和等於$T$，因此$JJBAP$為True
* 當$JJBAP$為True時，代表可以從$S$中取出一些數字$a_{b_{1}}...a_{b_{k}}$
使得$\Sigma^{m}_{i=1}a_{b_{i}}=T$ ($b_{i}$為一數列)
可以對兩邊同加上$nK$，$\Sigma^{m}_{i=1}(a_{b_{i}}^{'}+K)+(n-m)K=T+nK$
而$a_{i}$加上$K$和$K$會是$S^{'}$中的某個元素，且$m-n\le n$所以多加的K數量必不大於$n$
因此可以得到$\Sigma^{n}_{i=1}a_{b_{i}}^{'}=T+nK$，所以$JJBAP_{+}$也為True
* 而轉換需要計算出$K$並把$S$中元素都加上$K$，並且把$T$加上$nK$
    因此時間複雜度會是$O(n)$，為polynomial

由此可知，$JJBAP\le_{p} JJBAP_{+}$

### (2)

### (3)

定義$DDBP$是給定一數列且元素的weight都在$[0,1]$之間，要確定這串數列是否可以被分成k個bins使得bins的weight不超過1公斤

取$DDBP$是分成兩個bins
先把S中的元素都看過，如果有任何一個超過$\frac{U}{2}$則直接輸出false
若都沒有則$把S中的數字都除以\frac{U}{2}，得到S^{'}$
因為有先確定過S中元素都不大於$\frac{U}{2}$，因此$\{0 \le a\le 1|\forall a\in S^{'}\}$符合$DDBP的條件且此時S^{'}$的sum=2

因此當$DDBP$為True時，代表存在可以把$S^{'}$分成兩堆且兩堆的和都不大於1
因為$S^{'}$的和為2，所以若有一堆的和小於1，則另一堆的和必大於1
因此可以得到當$DDBP$為True時，代表可以把$S^{'}$分成和為1的兩堆
假設其中一堆為$b_{1}...b_{m}$，則有$\Sigma_{i=1}^{m}b_{i}=1$
兩邊同乘$\frac{U}{2}$，$\Sigma_{i=1}^{m}(\frac{U}{2}b_{i})=\frac{U}{2}$
而$S^{'}又是S除以\frac{U}{2}而來$，所以$\frac{U}{2}b_{i}\in S$
因此$QQP$也會得到True

當$QQP$為True時，代表可以把$S$分成大小相等的兩堆
把$S$中的元素都除以$\frac{U}{2}$後，因為所有元素必小於$\frac{U}{2}$
所以除完後所有元素必在[0,1]間，而等式就會變成有兩群元素各自的和是1，因此$DDBP$為True

而把$QQP$轉成$DDBP$要把$S$中所有元素都除以$\frac{U}{2}$，因此需要$O(n)$
由以上可以得出$QQP\le_{p} DDBP$，因此$QQP\le_{p} DBP$

### (4)
令$S分成兩組b_{1},b_{2}$是$QQP$的一組certificate，把$S$的總和算出來為$O(N)$
接著把$b_{1},b_{2}$各自的和算出來也是$O(N)$，最後把$b_{1},b_{2}$以及$S$的和做比較
因此$QQP$可以在polynomial time被verify，所以$QQP$是NP

令$S$分成$n$組$k_{1}...k_{n}$是$DDBP$的一組certificate
只要把$k_{1}...k_{n}$中每個元素加起來確認是否小於等於1就能verify $k_{1}...k_{n}$是一組解
因此$DDBP$是$NP$

### (5)
假設存在polynomial time $G-approximation$ for $DBP\ (G<\frac{3}{2}, G\in R)$ 
由$QQP$可知在$k=2$時為$NPC$問題
當正確答案為$2$時，因為$G<\frac{3}{2}$所以$2G<3且為正整數\ (bin數量必是整數)$
因此由$G-approximation$可以找出答案為2，但由題可知$P\ne NP$
所以必不可能在polynomial time找出答案為2的解，因此矛盾
所以不存在polynomial time $G-approximation$ for $DBP\ (G<\frac{3}{2})$ 
也就是polynomial time $(\frac{3}{2}-\epsilon)-approximation$ for $DBP\ (\epsilon>0)$ 

### (6)
$\Sigma_{i=1}^{\frac{1}{c}}H^{m}_{i}$
因為元素皆大於c所以取出的組合中最多會有$\frac{1}{c}$個元素，因此每組裡可能有1,2...$\frac{1}{c}$個元素
而這每一種可能的數量都是從m種元素中挑選出來的
令每種元素拿了$x_{1}...x_{m}$個，目前的組合中有k個元素$\to \Sigma_{i=1}^{m}x_{i}=k$
因此$x_{i}$的組合數最多會有$H^{m}_{k}$個，而全部加起來就是所求upper bound

### (7)
可以視為在最多$M$種放法中，對於每種可能取出$x_{1},x_{2}...x_{M}$
而由題目可知要取出k個放法，因此可以得到$\Sigma_{i=1}^{M}x_{i}=k$，所以$x_{i}$的組合會是$H^{M}_{k}$
$H^{M}_{k}=C^{M+k-1}_{k}=C^{M+k-1}_{M-1}$
而$C^{M+k-1}_{M-1}中共有M-1項$，且對於所有項而言$M+k-1$都會大於他們
因此可以得到$C^{M+k-1}_{M-1}<(M+k-1)^{M-1}$
又M是常數，取$c=M^{M-1}$,$ck^{M-1}=(MK)^{M-1}$
$(MK)^{M-1}-(M+k-1)^{M-1}=(MK-M-k+1)^{M-1}$
$=((M-1)(K-1))^{M-1}>0$，因此可以得到$(M+k-1)^{M-1}=O(k^{M-1})=O(k^M)$

### (8)
由(6)可知求出$M$的時間複雜度可以是$O(\frac{1}{c})=O(1)$
由(7)可知當有k個bins時，放的方法數會是$O(k^M)$
先算出每種球各有幾個，並算出$M$種取法各用到哪些球各幾個
接著從$k=1$開始看過所有放法中有沒有valid的，檢查是否valid需要$O(n)$
如果valid則當前的k即為所求
如此會跑過$O(1^M+2^M+...+k^M)$
假設複雜度為$d(1^M+...+k^M),d\in N$
令$c=d$，則對於所有$k>1$
$ck^{M+1}=c(k^M+k^M+...+k^M)$ (共k個)
$\to d(1^M+...+k^M)=c(1^M+...+k^M)<c(k^M+k^M+...+k^M)$
因此對於所有$k>1$，都能找到一個$c=d$使得$ck^{M+1}>d(1^M+2^M...+k^M)$
所以時間複雜度會是$O(k^{M+1})$
而$k$最多不會超過$n$，因此$O(k^{M+1})=O(n^{M+1})$
而計算$(c,m)-Kuan\ DDBP$時只要將$(c,m)-Kuan\ DBP$的答案和k比較即可，因此$(c,m)-Kuan\ DDBP$也可在多項式時間做出來，所以是$P$問題

## Problem 6
### (1)
G中每個頂點的degree都是偶數且G是connected
### (2)
當樹只有一個點時，degree為奇數的點是0個因此符合
假設當任意一棵樹在有$n$個vertex的時候degree為奇數的點有偶數個
則當樹上有$n+1$個vertex時，存在某棵vertex數為$n$的樹加上葉子$L$後會變成這棵樹
當$L$接在一個degree為奇數的vertex $K$上的話，則$K$的degree會變成偶數
但$L$的degree=1也是奇數，因此這棵樹degree為奇數的點一樣有偶數個
當$L$接在一個degree為偶數的vertex $K$上的話，則$K$的degree會變成奇數
$L$的degree=1也是奇數，所以這棵樹degree為奇數的點會多兩個，因此一樣是偶數
由數學歸納法得出，不論樹的大小為多少，樹上degree為奇數的點必有偶數個

### (3)
已知$OPT$的路徑會形成一個環$v_{1}...v_{k},v_{1}$，且圖滿足三角不等式
將$V^{'}$中的點沿著$OPT$路徑的順序排列後再將這些點照順序連接起來，會形成一個多邊形的環$K$且總$cost$必小於$OPT$，可以得到$cost(K)\le OPT$
而取得perfect matching的方式可以交錯取出$K$中的邊，取法會有兩種恰將$K$分成兩堆路徑
因此必有一種perfect matching $E$使得$cost(E)\le \frac{cost(K)}{2} \Rightarrow cost(E)\le \frac{cost(K)}{2} \le OPT/2$

而minimum cost perfect matching的cost(M)必會小於等於$E$的cost
所以得到$cost(M) \le cost(E)\le OPT/2$
因此可以得到$cost(M)\le OPT/2$

### (4)
* 先建構出圖上的$MST$，令其為$T$
* 接著挑出$T$上degree為奇數的頂點集，令其為$O$且由(2)可知$O$中有偶數個點
* 然後利用$Oracle$找出$O$在原圖上的perfect matching，令其為$M$
* 接著把$M$中的邊加到$T$裡面，令修改完的圖為$J$ (相同的邊加入時視為兩條)
* 如此一來可以得到$J$中的點degree都是偶數且connected，因此$J$中存在歐拉環
    * 因為$O$是$T$中degree為奇數的頂點集，且perfect matching會為每個點加上一條邊
        因此加回$T$後所有點的degree都會是偶數
* 接著找出圖上的歐拉環
    * 找歐拉環時，先選出一條沒走過的邊，接著一直走沒走過的邊，這樣走完所有點後會形成許多個環，接著把有交集的環的展開後連接起來，把所有點都做過後就能得到一個歐拉環
* 最後再把這個歐拉環改造成哈密頓cycle就是答案，改造的方式只要跳過歐拉環中重複的點就好

#### Prove:
假設最優解路徑為$I$，長度為$L(I)$、上述方法算出的路徑為$H$，路徑長為$L(H)$、最小生成樹的路徑為$T$，路徑長為$L(T)$、$E$為上面作法最後提到的歐拉環、degree為奇數的點集合為$O$，$M$為$O$上的minimum perfect matching，路徑長為$L(M)$

* $L(E)=L(T)+L(M)$且因為存在三角不等式所以$L(H)<L(E)$
* 又因為去掉$I$中任意一條路徑後，$I$就會變成一棵生成樹，所以$L(T)\le L(I)$
* 令$O$的optimal TSP路徑為$P$，由(3)可知$M$一定會小於$P$的cost的一半
    如此可以得到$L(M)\le \frac{L(P)}{2}$
* 又因為$O$只包含原圖中的部分點，因此$L(P)\le L(I)\to L(K)\le 0.5L(P)\le 0.5L(I)$
* 總和以上可知，$L(H)<L(E)=L(T)+L(M)\le L(I)+0.5L(I)=1.5L(I)$
  
#### Time complexity:
建構$MST$需要$O(ElogV)$
選出degree為奇數的頂點需要$O(V^2)$
構造minimum perfect matching是多項式時間
把$M$的邊加入$T$需要$O(E^2)$
找出並改造歐拉環都是多項式時間
因此全部的動作都能在polynomial time完成





