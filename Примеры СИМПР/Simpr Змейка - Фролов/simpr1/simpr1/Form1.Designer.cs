namespace simpr1
{
    partial class Form1
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.field = new System.Windows.Forms.PictureBox();
            this.button1 = new System.Windows.Forms.Button();
            this.head = new System.Windows.Forms.PictureBox();
            this.rocket = new System.Windows.Forms.PictureBox();
            this.wall = new System.Windows.Forms.PictureBox();
            this.fruit = new System.Windows.Forms.PictureBox();
            this.tail = new System.Windows.Forms.PictureBox();
            this.gamefield = new System.Windows.Forms.PictureBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.field)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.head)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.rocket)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.wall)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fruit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tail)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gamefield)).BeginInit();
            this.SuspendLayout();
            // 
            // field
            // 
            this.field.Image = ((System.Drawing.Image)(resources.GetObject("field.Image")));
            this.field.Location = new System.Drawing.Point(12, 12);
            this.field.Name = "field";
            this.field.Size = new System.Drawing.Size(601, 401);
            this.field.TabIndex = 0;
            this.field.TabStop = false;
            this.field.Visible = false;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 419);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(603, 72);
            this.button1.TabIndex = 1;
            this.button1.Text = "СТАРТ";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // head
            // 
            this.head.Image = ((System.Drawing.Image)(resources.GetObject("head.Image")));
            this.head.Location = new System.Drawing.Point(1, 0);
            this.head.Name = "head";
            this.head.Size = new System.Drawing.Size(21, 21);
            this.head.TabIndex = 2;
            this.head.TabStop = false;
            this.head.Visible = false;
            // 
            // rocket
            // 
            this.rocket.Image = ((System.Drawing.Image)(resources.GetObject("rocket.Image")));
            this.rocket.Location = new System.Drawing.Point(28, 0);
            this.rocket.Name = "rocket";
            this.rocket.Size = new System.Drawing.Size(21, 21);
            this.rocket.TabIndex = 3;
            this.rocket.TabStop = false;
            this.rocket.Visible = false;
            // 
            // wall
            // 
            this.wall.Image = ((System.Drawing.Image)(resources.GetObject("wall.Image")));
            this.wall.Location = new System.Drawing.Point(55, 0);
            this.wall.Name = "wall";
            this.wall.Size = new System.Drawing.Size(21, 21);
            this.wall.TabIndex = 4;
            this.wall.TabStop = false;
            this.wall.Visible = false;
            // 
            // fruit
            // 
            this.fruit.Image = ((System.Drawing.Image)(resources.GetObject("fruit.Image")));
            this.fruit.Location = new System.Drawing.Point(82, 0);
            this.fruit.Name = "fruit";
            this.fruit.Size = new System.Drawing.Size(21, 21);
            this.fruit.TabIndex = 5;
            this.fruit.TabStop = false;
            this.fruit.Visible = false;
            // 
            // tail
            // 
            this.tail.Image = ((System.Drawing.Image)(resources.GetObject("tail.Image")));
            this.tail.Location = new System.Drawing.Point(109, 0);
            this.tail.Name = "tail";
            this.tail.Size = new System.Drawing.Size(21, 21);
            this.tail.TabIndex = 6;
            this.tail.TabStop = false;
            this.tail.Visible = false;
            // 
            // gamefield
            // 
            this.gamefield.Image = ((System.Drawing.Image)(resources.GetObject("gamefield.Image")));
            this.gamefield.Location = new System.Drawing.Point(14, 12);
            this.gamefield.Name = "gamefield";
            this.gamefield.Size = new System.Drawing.Size(601, 401);
            this.gamefield.TabIndex = 7;
            this.gamefield.TabStop = false;
            // 
            // timer1
            // 
            this.timer1.Interval = 1;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 72F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(21, 165);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(583, 108);
            this.label1.TabIndex = 8;
            this.label1.Text = "Rocket WIN!";
            this.label1.Visible = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 72F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(-6, 165);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(652, 108);
            this.label2.TabIndex = 9;
            this.label2.Text = "Rocket LOSE!";
            this.label2.Visible = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(627, 503);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.gamefield);
            this.Controls.Add(this.tail);
            this.Controls.Add(this.fruit);
            this.Controls.Add(this.wall);
            this.Controls.Add(this.rocket);
            this.Controls.Add(this.head);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.field);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.field)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.head)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.rocket)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.wall)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fruit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tail)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gamefield)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox field;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.PictureBox head;
        private System.Windows.Forms.PictureBox rocket;
        private System.Windows.Forms.PictureBox wall;
        private System.Windows.Forms.PictureBox fruit;
        private System.Windows.Forms.PictureBox tail;
        private System.Windows.Forms.PictureBox gamefield;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

