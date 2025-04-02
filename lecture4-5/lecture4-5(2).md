# 线性表 Part2 笔记

---

## 2.4 线性表的链式存储结构

### 一、链表基本操作
1. **创建链表**  
   ```c
   Nodeptr createList(int n) {
       Nodeptr list = NULL, p, q;
       for (int i=0; i<n; i++) {
           q = (Nodeptr)malloc(sizeof(Node));
           q->data = read_data();  // 数据输入
           q->link = NULL;
           if (list == NULL) list = p = q;
           else { p->link = q; p = q; }
       }
       return list;
   }
   ```
   • **时间复杂度**：O(n)

2. **插入操作**  
   • 头插法：时间复杂度 O(1)  
     ```c
     Nodeptr insertFirst(Nodeptr list, ElemType elem) {
         Nodeptr p = (Nodeptr)malloc(sizeof(Node));
         p->data = elem;
         p->link = list;
         return p;  // 返回新头节点 不要
     }
     ```
     **不要直接令 list = p，（局部）在函数结束后list依然指向了第二个**
   • 指定位置插入：时间复杂度 O(n)  
     ```c
     void insertAfter(Nodeptr p, ElemType elem) {
         Nodeptr q = (Nodeptr)malloc(sizeof(Node));
         q->data = elem;
         q->link = p->link;
         p->link = q;
     }
     ```

3. **删除操作**  
   • 删除指定节点（需前驱指针）：时间复杂度 O(1)  
     ```c
     void deleteNode(Nodeptr prev, Nodeptr p) {
         prev->link = p->link;
         free(p);
     }
     ```

---

### 二、循环链表
1. **结构特点**  
   • 尾节点指针域指向头节点  
   • 判空条件：`p->link == list`（非空时）

---

### 三、双向链表
1. **结构定义**  
**双向链表结构示意**
`HEAD ⇄ [A] ⇄ [B] ⇄ [C] ⇄ HEAD（循环双向链表）`
   ```c
   typedef struct DNode {
       ElemType data;
       struct DNode *llink, *rlink;
   } DNode, *DNodeptr;
   ```
1. **插入操作** 
```c
void insertAfter(DNodeptr p, ElemType elem) {
    DNodeptr q = (DNodeptr)malloc(sizeof(DNode));
    q->data = elem; // Q 新加入的节点
    
    // 关键指针调整（四步操作）
    q->llink = p;         // 1. Q前驱指向P
    q->rlink = p->rlink;  // 2. Q后继指向原P的后继
    p->rlink->llink = q;  // 3. 原P后继的前驱指向Q
    p->rlink = q;         // 4. P的后继指向Q
}
```
**头插**
```c
DNodeptr insertHead(DNodeptr list, ElemType elem) {
    DNodeptr q = (DNodeptr)malloc(sizeof(DNode));
    q->data = elem; // Q 新加入的节点
    //! 不要直接移动头节点
    q -> rlink = list;
    q -> llink = list -> llink; //循环列表
    list -> llink -> rlink = q;
    list -> llink = q;
    //最后移动 
    return q;
}
```

2. **删除操作**  
   ```c
   void deleteDNode(DNodeptr p) {
       p->llink->rlink = p->rlink;
       p->rlink->llink = p->llink;
       free(p);
   }
   ```

---

## 四、应用实例
### 2. 多项式相加
• **算法步骤**  
  1. 遍历链表A和B，按指数降序合并  
  2. 指数相同则系数相加，不同则插入较大项  
  ```c
  void addPolynomial(Nodeptr a, Nodeptr b) {
      Nodeptr p = a, q = b;
      while (p && q) {
          if (p->exp == q->exp) {
              p->coef += q->coef;
              q = q->link;
          } else if (p->exp > q->exp) {
              insertNode(p, q->coef, q->exp);
              q = q->link;
          }
          p = p->link;
      }
  }
  ```

---

## 五、链式存储的优缺点
| **优点**                     | **缺点**                     |
|------------------------------|-------------------------------|
| 动态内存分配（无需预知规模） | 需要额外存储指针域（空间开销）|
| 插入/删除高效（O(1)）        | 随机访问效率低（O(n)）        |
| 无内存碎片                   | 实现复杂度较高（循环/双向）  |
|                             | 不能使用折半查找等高效方法  |

---
## 六、注意点：
1. **头指针保护原则**  
   ```c
   // 错误操作示例
   DNodeptr list = createList();
   list = list->rlink;  // 直接移动头指针，导致链表断裂！
   
   // 正确做法：使用辅助指针
   DNodeptr p = list->rlink;
   ```

2. **边界处理四要素**  
   • 插入/删除头节点时，需要特殊处理`HEAD->llink`
   • 插入/删除尾节点时，需要处理`HEAD->rlink`
   • 空链表时`HEAD->llink = HEAD->rlink = HEAD`
   • 单节点链表操作需保证自循环

3. **内存管理铁律**  
   ```c
   DNodeptr p = (DNodeptr)malloc(sizeof(DNode));
   // 必须立即初始化指针！
   p->llink = NULL;
   p->rlink = NULL;
   ```


