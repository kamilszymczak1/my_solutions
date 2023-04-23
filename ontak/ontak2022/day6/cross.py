import pygame

class Vector2D:
    def __init__ (self, a):
        self.x = a[0]
        self.y = a[1]

    def __add__ (self, v):
        return Vector2D((self.x + v.x, self.y + v.y))
    
    def __sub__ (self, v):
        return Vector2D((self.x - v.x, self.y - v.y))
    
    def __mul__ (self, v):
        return self.x * v.y - self.y * v.x
    
    def to_tuple(self):
        return (self.x, self.y)


pygame.init()

HEIGHT = 1000
WIDTH = 1000

screen = pygame.display.set_mode((HEIGHT, WIDTH))

V = Vector2D((300, 300))
center = Vector2D((HEIGHT // 2, WIDTH // 2))

running = True

while running:
    
    mouse = Vector2D(pygame.mouse.get_pos()) - center
    
    if mouse * V <= 0:
        screen.fill((255, 255, 255))
    else:
        screen.fill((0, 0, 0))
    
    pygame.draw.line(screen, 255, center.to_tuple(), (center + mouse).to_tuple())
    pygame.draw.line(screen, 255, center.to_tuple(), (center + V).to_tuple())
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    pygame.display.update()
    
