@auth.requires_login()
def index():
    items = db().select(db.sell.ALL, orderby=db.sell.title)
    return dict(items=items)

def show():
    item = db.sell(request.args(0,cast=int)) or redirect(URL('index'))
    return dict(item=item)

def download():
    return response.download(request, db)

def user():
    return dict(form=auth())

def display_form():
   form = SQLFORM(db.sell)
   if form.process().accepted:
       response.flash = 'form accepted'
   elif form.errors:
       response.flash = 'form has errors'
   else:
       response.flash = 'please fill out the form'
   form.add_button('Back', URL("index"))
   return dict(form=form)
